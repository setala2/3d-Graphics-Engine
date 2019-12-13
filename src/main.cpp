#include "GL/glew.h"

#include "GlfwManager.h"
#include "ImguiManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

int main()
{
	GlfwManager glfwManager;

	constexpr unsigned int windowWidth = 1600;
	constexpr unsigned int windowHeight = 900;

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

	as3d::Renderer renderer;
	renderer.SetClearColor();
	renderer.EnableDepthTesting(true);
	renderer.EnableBackFaceCulling(true);

	shader.Bind();

	float cubePosition[3] = { 0 };
	float cubeRotation[3] = { 0 };
	float cubeScale[3] = { 1, 1, 1 };

	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scale;

	glm::mat4 model;
	glm::mat4 view(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)windowWidth / (float)windowHeight, 0.01f, 20.0f);

	glm::mat4 mvp;

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(cubePosition[0], cubePosition[1], cubePosition[2] - 10.0f));
		rotation = glm::mat4(1.0f);
		rotation = glm::rotate(rotation, glm::radians(cubeRotation[1]), glm::vec3(0,1,0));
		rotation = glm::rotate(rotation, glm::radians(cubeRotation[0]), glm::vec3(1,0,0));
		rotation = glm::rotate(rotation, glm::radians(cubeRotation[2]), glm::vec3(0,0,1));
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(cubeScale[0], cubeScale[1], cubeScale[2]));

		model = translation * rotation * scale;
		mvp = projection * view * model;
		shader.SetMatrix4("mvp", mvp);

		imgui.BeginFrame();

		ImGui::Begin("Cube controls");
		ImGui::SliderFloat3("position", cubePosition, -10.0f, 10.0f);
		ImGui::SliderFloat3("rotation", cubeRotation, -180.0f, 180.0f);
		ImGui::SliderFloat3("scale", cubeScale, 0.5f, 1.5f);
		ImGui::End();

		renderer.Draw(va, ib, shader);

		imgui.EndFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}