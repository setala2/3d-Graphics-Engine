#pragma once

// A simple debugging tool for gl functions.
// Implementation of glCheckError_ copied from https://learnopengl.com/In-Practice/Debugging

#include <string>
#include <iostream>
#include "GL/glew.h"

unsigned int glCheckError_(const char* file, int line);

#define glCheckError(x) x; glCheckError_(__FILE__, __LINE__) 