#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class ImguiManager
{
	static unsigned int refCount;
public:
	ImguiManager(GLFWwindow* window);
	~ImguiManager();

	void BeginFrame();
	void EndFrame();
};