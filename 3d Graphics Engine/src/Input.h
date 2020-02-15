#pragma once

#include <GLFW/glfw3.h>

namespace as3d
{
	class Input
	{
	public:
		static void Init(GLFWwindow* window);
		static bool IsKeyPressed(int keycode);
	private:
		static GLFWwindow* window;
	};
}