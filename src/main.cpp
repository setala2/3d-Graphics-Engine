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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Objloader/OBJ_Loader.h"

#include <vector>

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

	lightModel.SetPosition(2, 5, -2);
	lightModel.SetScale(0.25f);

	///////////////////////////////////////////////////
	//
	//		Load and configure the teapot model
	//
	///////////////////////////////////////////////////

	// Load an object file using the loader library
	objl::Loader objLoader;
	objLoader.LoadFile("src/models/teapot.obj");
	const auto& vertexVector = objLoader.LoadedVertices;
	const auto& indexVector = objLoader.LoadedIndices;

	// Copy the vertex position data to a local buffer (Ignore normals and texture coordinates for now)
	float* vertices = new float[vertexVector.size() * 3];
	for (objl::Vertex v : vertexVector)
	{
		static unsigned int index = 0;
		vertices[index++] = v.Position.X;
		vertices[index++] = v.Position.Y;
		vertices[index++] = v.Position.Z;
	}

	// Create the buffer on the GPU and free the memory on the CPU side.
	as3d::VertexBuffer teapotVb(vertices, 3 * sizeof(float) * vertexVector.size());
	delete[] vertices;

	as3d::VertexArray teapotVa;

	as3d::BufferLayout teapotLayout;
	teapotLayout.Push<float>(3);
	teapotVa.AddBuffer(teapotVb, teapotLayout);

	as3d::IndexBuffer teapotIb(indexVector.data(), indexVector.size());

	as3d::Shader teapotShader("src/shaders/vertex.glsl", "src/shaders/frag_phong.glsl");
	teapotShader.Bind();
	teapotShader.SetFloat("ambientIntensity", 0.2f);
	teapotShader.SetVector3("ambientColor", 0.8f, 1.0f, 0.1f);

	as3d::Mesh teapotMesh(&teapotVa, &teapotIb);
	as3d::Model teapotModel(&teapotMesh, &teapotShader);

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

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		glm::mat4 vpMatrix = camera.GetViewProjectionMatrix();

		mvp = vpMatrix * teapotModel.GetModelMatrix();
		teapotShader.Bind();
		teapotShader.SetMatrix4("mvp", mvp);
		renderer.Draw(teapotModel);

		mvp = vpMatrix * lightModel.GetModelMatrix();
		lightShader.Bind();
		lightShader.SetMatrix4("mvp", mvp);
		renderer.Draw(lightModel);

		imgui.BeginFrame();
		teapotModel.DrawControlWindow("Teapot controls");
		lightModel.DrawControlWindow("Light controls");
		renderer.DrawControlWindow("Renderer controls");
		camera.DrawControlWindow("Camera controls");
		imgui.EndFrame();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}