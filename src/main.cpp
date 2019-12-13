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

	float vertices[] = { -0.5f, -0.5f, 0.0f,
						  0.0f,  0.5f, 0.0f,
						  0.5f, -0.5f, 0.0f };

	unsigned int indices[] = { 0,2,1 };

	as3d::VertexArray va;

	as3d::VertexBuffer vb(vertices, sizeof(vertices));

	as3d::BufferLayout layout;
	layout.Push<float>(3);

	va.AddBuffer(vb, layout);

	as3d::IndexBuffer ib(indices, 3);

	as3d::Shader shader("src/shaders/vertex.glsl", "src/shaders/frag.glsl");

	as3d::Renderer renderer;
	renderer.SetClearColor(0, 1, 0);
	renderer.EnableBackFaceCull(true);

	glm::mat4 translation;
	shader.Bind();

	float triangleOffset[3] = { 0 };

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear(GL_COLOR_BUFFER_BIT);
		
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(triangleOffset[0], triangleOffset[1], triangleOffset[2]));
		shader.SetMatrix4("translation", translation);

		imgui.BeginFrame();

		ImGui::Begin("triangle");
		ImGui::SliderFloat3("Triangle position", triangleOffset, -0.5f, 0.5f);
		ImGui::End();

		renderer.Draw(va, ib, shader);

		imgui.EndFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}