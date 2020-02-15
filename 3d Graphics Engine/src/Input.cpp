#include "Input.h"

namespace as3d
{
	GLFWwindow* Input::window = nullptr;

	void Input::Init(GLFWwindow* window)
	{
		Input::window = window;
	}

	bool Input::IsKeyPressed(int keycode)
	{
		int state = glfwGetKey(window, keycode);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}
}