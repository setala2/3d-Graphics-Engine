#include "GL/glew.h"

#include "Gldebug.h"
#include "GlfwManager.h"

#include <iostream>

int main()
{
	GlfwManager glfwManager;

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Test window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();
	glCheckError(glClearColor(0, 1, 0, 1));

	while (!glfwWindowShouldClose(window))
	{
		glCheckError(glClear(GL_COLOR_BUFFER_BIT));
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	return 0;
}