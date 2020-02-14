#pragma once
#include <GLFW/glfw3.h>

namespace as3d
{
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		void Update();

		inline unsigned int GetWidth() const  { return width; }
		inline unsigned int GetHeight() const { return height; }

		inline GLFWwindow* GetPointer() const { return glfwPointer; }
		inline bool ShouldClose() const { return glfwWindowShouldClose(glfwPointer); }
		inline void MakeCurrent() { glfwMakeContextCurrent(glfwPointer); }

	private:
		unsigned int width, height;
		const char* title;

		GLFWwindow* glfwPointer;

		static int windowCount;
	};
}