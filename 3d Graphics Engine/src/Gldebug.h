#pragma once

// A simple debugging tool for gl functions.
// Implementation of glCheckError_ copied from https://learnopengl.com/In-Practice/Debugging

#include <string>
#include <iostream>
#include "GL/glew.h"

bool glCheckError_(const char* file, int line);

#ifdef ASSERT_GL_ERRORS
	#include <cassert>
	#define glCheckError(x) x; assert(glCheckError_(__FILE__, __LINE__))
#else
	#define glCheckError(x) x; glCheckError_(__FILE__, __LINE__)
#endif
