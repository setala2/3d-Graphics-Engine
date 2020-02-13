#include "GlfwManager.h"

unsigned int GlfwManager::refCount = 0;

GlfwManager::GlfwManager()
{
	if (refCount++ == 0)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
}

GlfwManager::~GlfwManager()
{
	if (--refCount == 0)
		glfwTerminate();
}
