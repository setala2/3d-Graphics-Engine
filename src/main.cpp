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

	float cubeVertices[] = {
		// Position				// Color

		// Top right front
		1.0f, 1.0f, 1.0f,		1.0f,   1.0f,  1.0f,
		// Top left front
		-1.0f, 1.0f, 1.0f,		0.0f,   1.0f,  1.0f,
		// Bottom right front
		1.0f, -1.0f, 1.0f,		1.0f,   0.0f,  1.0f,
		// Bottom left front
		-1.0f, -1.0f, 1.0f,		0.0f,   0.0f,  1.0f,
		// Top right back
		1.0f, 1.0f, -1.0f,		1.0f,   1.0f,  0.0f,
		// Top left back
		-1.0f, 1.0f, -1.0f,		0.0f,   1.0f,  0.0f,
		// Bottom right back
		1.0f, -1.0f, -1.0f,		1.0f,   0.0f,  0.0f,
		// Bottom left back
		-1.0f, -1.0f, -1.0f,	0.0f,   0.0f,  0.0f
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

	// Load an object file using the loader library
	objl::Loader objLoader;
	objLoader.LoadFile("src/models/cube.obj");
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

	as3d::VertexArray va;

	as3d::VertexBuffer vb(vertices, 3 * sizeof(float) * vertexVector.size());

	delete[] vertices;

	as3d::BufferLayout layout;
	layout.Push<float>(3);	// Positions
	va.AddBuffer(vb, layout);

	as3d::IndexBuffer ib(indexVector.data(), indexVector.size());

	as3d::Shader shader("src/shaders/vertex.glsl", "src/shaders/frag.glsl");

	as3d::Mesh cubeMesh(&va, &ib);
	as3d::Model cubeModel(&cubeMesh, &shader);

	as3d::Renderer renderer;

	shader.Bind();

	glm::mat4 model;
	as3d::Camera camera(glm::perspective(glm::radians(60.0f), aspectRatio, 0.01f, 20.0f));

	glm::mat4 mvp;

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		model = cubeModel.GetModelMatrix();
		mvp = camera.GetViewProjectionMatrix() * model;
		shader.SetMatrix4("mvp", mvp);
		renderer.Draw(cubeModel);

		imgui.BeginFrame();
		cubeModel.DrawControlWindow("Cube controls");
		renderer.DrawControlWindow("Renderer controls");
		camera.DrawControlWindow("Camera controls");
		imgui.EndFrame();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}