#include "Window.h"
#include "Input.h"

#include <iostream>
#include <cassert>

namespace as3d
{
	int Window::windowCount = 0;

	Window::Window(unsigned int width, unsigned int height, const char* title)
		: title(title), width(width), height(height)
	{
		if (windowCount == 0)
		{
			int success = glfwInit();
			if (!success)
			{
				std::cout << "Couldn't initialize glfw!" << std::endl;
				assert(false);
			}
		}

		glfwPointer = glfwCreateWindow(width, height, title, nullptr, nullptr);
		Input::Init(glfwPointer);

		currentTime = glfwGetTime();
		++windowCount;
	}

	Window::~Window()
	{
		glfwDestroyWindow(glfwPointer);
		if(--windowCount == 0)
			glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(glfwPointer);
		timeSinceUpdate = static_cast<float>(glfwGetTime() - currentTime);
		currentTime = glfwGetTime();
	}
}
