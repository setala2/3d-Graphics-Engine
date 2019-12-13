#include "GL/glew.h"

#include "Gldebug.h"
#include "GlfwManager.h"
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

	float x = 0;
	bool right = true;

	glm::mat4 translation;
	shader.Bind();
	GLint u_Translation = shader.GetUniformLocation("translation");

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
		glUniformMatrix4fv(u_Translation, 1, GL_FALSE, &(translation[0][0]));

		renderer.Draw(va, ib, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}