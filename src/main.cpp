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

#include <iostream>

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


	float vertices[] = { -3.0f, -3.0f, 0.0f,
						  0.0f,  3.0f, 0.0f,
						  3.0f, -3.0f, 0.0f };

	unsigned int indices[] = { 0,2,1 };

	as3d::VertexArray va;

	as3d::VertexBuffer vb(cubeVertices, sizeof(cubeVertices));

	as3d::BufferLayout layout;
	layout.Push<float>(3);	// Positions
	layout.Push<float>(3);	// Colors

	va.AddBuffer(vb, layout);

	as3d::IndexBuffer ib(cubeIndices, 36);

	as3d::Shader shader("src/shaders/vertex.glsl", "src/shaders/frag.glsl");

	as3d::Mesh cubeMesh(&va, &ib);
	as3d::Model cubeModel(&cubeMesh, &shader);

	as3d::Renderer renderer;
	renderer.EnableDepthTesting(true);
	renderer.EnableBackFaceCulling(false);

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
		imgui.EndFrame();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}