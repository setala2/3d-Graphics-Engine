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

	float vertices[] = { -3.0f, -3.0f, 0.0f,
						  0.0f,  3.0f, 0.0f,
						  3.0f, -3.0f, 0.0f };

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

	shader.Bind();

	float trianglePosition[3] = { 0 };
	float triangleRotation = 0;
	float triangleScale[3] = { 1, 1, 1 };

	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scale;

	glm::mat4 model;
	glm::mat4 view(1.0f);
	glm::mat4 projection = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f);

	glm::mat4 mvp;

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear(GL_COLOR_BUFFER_BIT);
		
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(trianglePosition[0], trianglePosition[1], trianglePosition[2]));
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(triangleRotation), glm::vec3(0,0,1));
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(triangleScale[0], triangleScale[1], triangleScale[2]));

		model = translation * rotation * scale;
		mvp = projection * view * model;
		shader.SetMatrix4("mvp", mvp);

		imgui.BeginFrame();

		ImGui::Begin("Triangle controls");
		ImGui::SliderFloat3("position", trianglePosition, -3.0f, 3.0f);
		ImGui::SliderFloat("rotation", &triangleRotation, -180.0f, 180.0f);
		ImGui::SliderFloat3("scale", triangleScale, 0.5f, 1.5f);
		ImGui::End();

		renderer.Draw(va, ib, shader);

		imgui.EndFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}