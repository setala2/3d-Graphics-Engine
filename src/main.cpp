#include "GL/glew.h"

#include "Gldebug.h"
#include "GlfwManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Renderer.h"

#include <iostream>

int main()
{
	GlfwManager glfwManager;

	constexpr unsigned int windowWidth = 1600;
	constexpr unsigned int windowHeight = 900;

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Test window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();

	float vertices[] = { -0.5f, -0.5f, 0.0f,
						  0.0f,  0.5f, 0.0f,
						  0.5f, -0.5f, 0.0f };

	unsigned int indices[] = { 0,1,2 };

	as3d::VertexArray va;

	as3d::VertexBuffer vb(vertices, sizeof(vertices));

	as3d::BufferLayout layout;
	layout.Push<float>(3);

	va.AddBuffer(vb, layout);

	as3d::IndexBuffer ib(indices, 3);

	as3d::Shader shader("src/shaders/vertex.glsl", "src/shaders/frag.glsl");

	as3d::Renderer renderer;

	glCheckError(glClearColor(0, 1, 0, 1));

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear(GL_COLOR_BUFFER_BIT);
		renderer.Draw(va, ib, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}