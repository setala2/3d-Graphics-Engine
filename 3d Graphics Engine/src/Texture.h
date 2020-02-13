#pragma once
#include "Gldebug.h"

namespace as3d
{
	class Texture
	{
		GLuint handle;

		int width;
		int height;
		int nChannels;

	public:
		Texture(const char* path);
		~Texture() = default;

		void Bind(unsigned int slot = 0);
		void Unbind();
	};
}