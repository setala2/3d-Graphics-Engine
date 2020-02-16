#include "TextureCubemap.h"

#include "stb_image.h"

namespace as3d
{
	TextureCubemap::TextureCubemap(const std::vector<std::string>& filenames)
	{
		glCheckError(glGenTextures(1, &handle));
		glCheckError(glBindTexture(GL_TEXTURE_CUBE_MAP, handle));

		LoadTexture(filenames);
	}

	TextureCubemap::~TextureCubemap()
	{
		glDeleteTextures(1, &handle);
	}

	void TextureCubemap::LoadTexture(const std::vector<std::string>& filenames)
	{
		int width, height, channels;
		for (std::size_t i = 0; i < filenames.size(); ++i)
		{
			unsigned char* data = stbi_load(filenames[i].c_str(), &width, &height, &channels, 4);
			if (data)
			{
				glCheckError(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
			}
			else
			{
				std::cout << "Could not load texture: " << filenames[i] << std::endl;
			}
			stbi_image_free(data);
		}
		glCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		glCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		glCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		glCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	}

	void TextureCubemap::Bind() const
	{
		glCheckError(glBindTexture(GL_TEXTURE_CUBE_MAP, handle));
	}

	void TextureCubemap::Unbind() const
	{
		glCheckError(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}
}