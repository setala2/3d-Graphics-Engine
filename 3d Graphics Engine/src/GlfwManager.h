#pragma once
#include "GLFW/glfw3.h"

// A simple class that initializes and terminates glfw

class GlfwManager
{
	static unsigned int refCount;
public:
	GlfwManager();
	~GlfwManager();
};

