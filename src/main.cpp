#include "GL/glew.h"

#include "GlfwManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

int main()
{
	GlfwManager glfwManager;

	constexpr unsigned int windowWidth = 1600;
	constexpr unsigned int windowHeight = 900;

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Test window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

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

	float x = 0;
	bool right = true;

	glm::mat4 translation;
	shader.Bind();


	bool show_demo_window = true;

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear(GL_COLOR_BUFFER_BIT);
		
		if (x > 0.5f)
			right = false;
		if (x < -0.5f)
			right = true;

		if (right)
			x += 0.01f;
		else
			x -= 0.01f;
		
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0, 0));
		shader.SetMatrix4("translation", translation);


		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);


		renderer.Draw(va, ib, shader);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	return 0;
}