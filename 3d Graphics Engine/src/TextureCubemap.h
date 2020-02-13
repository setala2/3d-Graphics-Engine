#pragma once

#include "Gldebug.h"

#include <vector>
#include <string>

namespace as3d
{
	class TextureCubemap
	{
		GLuint handle;

	public:
		TextureCubemap(const std::vector<std::string>& filenames);
		~TextureCubemap();
		
		void LoadTexture(const std::vector<std::string>& filenames);

		void Bind() const;
		void Unbind() const;
	};
}