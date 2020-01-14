#include "GL/glew.h"

#include "GlfwManager.h"
#include "ImguiManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include "LightSource.h"
#include "Texture.h"
#include "Drawable.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "Objloader/OBJ_Loader.h"

#include <vector>
#include <cmath>

int main()
{
	GlfwManager glfwManager;

	constexpr unsigned int windowWidth = 1600;
	constexpr unsigned int windowHeight = 900;
	constexpr float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Test window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	ImguiManager imgui(window);

	glewInit();

	///////////////////////////////////////////////////
	//
	//		Create a cube shaped model to
	//		show the position of the light
	//
	///////////////////////////////////////////////////

	float cubeVertices[] = {
		// Position				// Color

		// Top right front
		1.0f, 1.0f, 1.0f,		// 1.0f,   1.0f,  1.0f,
		// Top left front		// 
		-1.0f, 1.0f, 1.0f,		// 0.0f,   1.0f,  1.0f,
		// Bottom right front	// 
		1.0f, -1.0f, 1.0f,		// 1.0f,   0.0f,  1.0f,
		// Bottom left front	// 
		-1.0f, -1.0f, 1.0f,		// 0.0f,   0.0f,  1.0f,
		// Top right back		// 
		1.0f, 1.0f, -1.0f,		// 1.0f,   1.0f,  0.0f,
		// Top left back		// 
		-1.0f, 1.0f, -1.0f,		// 0.0f,   1.0f,  0.0f,
		// Bottom right back	// 
		1.0f, -1.0f, -1.0f,		// 1.0f,   0.0f,  0.0f,
		// Bottom left back		// 
		-1.0f, -1.0f, -1.0f,	// 0.0f,   0.0f,  0.0f
	};

	unsigned int cubeIndices[] = {
		// Front
		0,1,2,
		1,3,2,
		// Back
		5,4,6,
		5,6,7,
		// Top
		5,0,4,
		5,1,0,
		// Bottom
		2,3,6,
		3,7,6,
		// Left
		1,5,3,
		5,7,3,
		// Right
		4,0,6,
		0,2,6
	};

	as3d::VertexBuffer lightVb(cubeVertices, sizeof(cubeVertices));
	as3d::IndexBuffer lightIb(cubeIndices, 36);

	as3d::BufferLayout lightLayout;
	lightLayout.Push<float>(3);

	as3d::VertexArray lightVa;
	lightVa.AddBuffer(lightVb, lightLayout);

	// Going to use the same shader files as the teapot, for now at least
	as3d::Shader lightShader("src/shaders/vertex.glsl", "src/shaders/frag.glsl");

	as3d::Mesh lightMesh(&lightVa, &lightIb);
	as3d::Model lightModel(&lightMesh, &lightShader);
	as3d::LightSource lightObject(&lightModel);

	lightObject.SetPosition(2, 5, -2);
	lightObject.SetScale(0.25f);

	///////////////////////////////////////////////////
	//
	//		Load and configure the textureCube model
	//
	///////////////////////////////////////////////////

	// Load an object file using the loader library
	objl::Loader objLoader;
	objLoader.LoadFile("src/models/cube2.obj");
	const auto& vertexVector = objLoader.LoadedVertices;
	const auto& indexVector = objLoader.LoadedIndices;

	// Copy the vertex position and normal data to a local buffer (Ignore texture coordinates for now)
	float* vertices = new float[vertexVector.size() * 8];
	for (objl::Vertex v : vertexVector)
	{
		static unsigned int index = 0;
		vertices[index++] = v.Position.X;
		vertices[index++] = v.Position.Y;
		vertices[index++] = v.Position.Z;
		vertices[index++] = v.Normal.X;
		vertices[index++] = v.Normal.Y;
		vertices[index++] = v.Normal.Z;
		vertices[index++] = v.TextureCoordinate.X;
		vertices[index++] = v.TextureCoordinate.Y;
	}

	// Create the buffer on the GPU and free the memory on the CPU side.
	as3d::VertexBuffer textureCubeVb(vertices, 8 * sizeof(float) * vertexVector.size());
	delete[] vertices;

	as3d::VertexArray textureCubeVa;

	as3d::BufferLayout textureCubeLayout;
	textureCubeLayout.Push<float>(3);	// Position
	textureCubeLayout.Push<float>(3);	// Normal
	textureCubeLayout.Push<float>(2);	// UV
	textureCubeVa.AddBuffer(textureCubeVb, textureCubeLayout);

	as3d::IndexBuffer textureCubeIb(indexVector.data(), indexVector.size());

	as3d::Shader textureCubeShader("src/shaders/vertex_lighting_map.glsl", "src/shaders/frag_lighting_map.glsl");
	textureCubeShader.Bind();

	as3d::Mesh textureCubeMesh(&textureCubeVa, &textureCubeIb);
	as3d::Model textureCubeModel(&textureCubeMesh, &textureCubeShader);
	as3d::Drawable textureCubeObject(&textureCubeModel);

	as3d::Texture diffuseMap("src/textures/container2.png");
	textureCubeShader.SetInt("material.diffuse", 0);	// Set the texture slot to 0

	as3d::Texture specularMap("src/textures/container2_specular.png");
	textureCubeShader.SetInt("material.specular", 1);	// Set the texture slot to 1

	///////////////////////////////////////////////////
	//
	//		Create the renderer and the camera
	//
	///////////////////////////////////////////////////

	as3d::Renderer renderer;

	as3d::Camera camera(glm::perspective(glm::radians(60.0f), aspectRatio, 0.01f, 20.0f));

	glm::mat4 mvp;

	///////////////////////////////////////////////////
	//
	//		Start the loop
	//
	///////////////////////////////////////////////////

	renderer.SetClearColor(1.0f);

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		glm::mat4 vpMatrix = camera.GetViewProjectionMatrix();

		//mvp = vpMatrix * textureCubeModel.GetModelMatrix();
		textureCubeShader.Bind();

		diffuseMap.Bind(0);
		specularMap.Bind(1);

		textureCubeShader.SetVector3("light.ambient", lightObject.GetAmbient());
		textureCubeShader.SetVector3("light.diffuse", lightObject.GetDiffuse());
		textureCubeShader.SetVector3("light.specular", lightObject.GetSpecular());
		textureCubeShader.SetVector3("light.position", lightObject.GetPosition());
		textureCubeShader.SetInt("material.shininess", static_cast<int>(std::pow(2, textureCubeModel.GetMaterial().shininess)));
		textureCubeShader.SetVector3("viewPosition", camera.GetPosition());
		textureCubeShader.SetMatrix4("viewProjection", vpMatrix);

		textureCubeShader.SetMatrix4("model", textureCubeObject.GetModelMatrix());
		textureCubeShader.SetMatrix3("normalMatrix", glm::inverseTranspose(textureCubeObject.GetModelMatrix()));

		renderer.Draw(textureCubeObject);

		mvp = vpMatrix * lightObject.GetModelMatrix();
		lightShader.Bind();
		lightShader.SetMatrix4("mvp", mvp);
		renderer.Draw(lightObject);

		imgui.BeginFrame();
		textureCubeObject.DrawControlWindow("TextureCube controls");
		lightObject.DrawControlWindow("Light controls");
		renderer.DrawControlWindow("Renderer controls");
		camera.DrawControlWindow("Camera controls");
		imgui.EndFrame();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}