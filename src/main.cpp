#include "GL/glew.h"

#include "Gldebug.h"
#include "GlfwManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>

int main()
{
	GlfwManager glfwManager;

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Test window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();

	float vertices[] = { -0.5f, -0.5f,
						  0.0f,  0.5f,
						  0.5f, -0.5f };

	unsigned int indices[] = { 0,1,2 };

	GLuint vao;
	glCheckError(glGenVertexArrays(1, &vao));
	glCheckError(glBindVertexArray(vao));

	as3d::VertexBuffer vb(vertices, sizeof(vertices));
	vb.Bind();

	as3d::IndexBuffer ib(indices, 3);
	ib.Bind();

	glCheckError(glEnableVertexAttribArray(0));
	glCheckError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));

	as3d::Shader shader("src/shaders/vertex.glsl", "src/shaders/frag.glsl");
	shader.Bind();

	glCheckError(glClearColor(0, 1, 0, 1));

	while (!glfwWindowShouldClose(window))
	{
		glCheckError(glClear(GL_COLOR_BUFFER_BIT));

		glCheckError(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetType(), NULL));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}