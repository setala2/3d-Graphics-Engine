#pragma once
#include "Gldebug.h"
#include <string>

namespace as3d
{
	class Texture
	{
		GLuint handle;

		int width;
		int height;
		int nChannels;

		std::string type = "";
		std::string path = "";

	public:
		Texture(const char* path);
		~Texture() = default;

		void Bind(unsigned int slot = 0);
		void Unbind();
	};
}