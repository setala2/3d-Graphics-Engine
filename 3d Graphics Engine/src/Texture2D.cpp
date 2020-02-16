#include "Texture2D.h"
#include "stb_image.h"

namespace as3d
{
	Texture2D::Texture2D(const std::string& path, const std::string& directory, const std::string& type)
		: path(path), type(type)
	{
		LoadFromFile(path, directory);
	}

	void Texture2D::Bind(unsigned int slot)
	{
		glCheckError(glActiveTexture(GL_TEXTURE0 + slot));	// The GL_TEXTURE slot enums are consecutive numbers so we can do this
		glCheckError(glBindTexture(GL_TEXTURE_2D, handle));
	}

	void Texture2D::Unbind()
	{
		glCheckError(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture2D::LoadFromFile(const std::string& path, const std::string& directory)
	{
		// Mostly copied from https://learnopengl.com/Lighting/Lighting-maps
		std::string fullPath;
		if (directory != "")
			fullPath = directory + "/" + path;
		else
			fullPath = path;

		glCheckError(glGenTextures(1, &handle));
		stbi_uc* imageData = stbi_load(fullPath.c_str(), &width, &height, &nChannels, 0);
		if (imageData)
		{
			GLenum format;
			switch (nChannels)
			{
			case 1: format = GL_RED; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
			default:
				std::cout << "Unknown pixel format: " << nChannels << " channels." << path << '\n';
				stbi_image_free(imageData);
				return;
			}

			glCheckError(glBindTexture(GL_TEXTURE_2D, handle));
			glCheckError(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData));

			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		}
		else
			std::cout << "Failed to load a texture: " << fullPath << '\n';

		stbi_image_free(imageData);
		glCheckError(glBindTexture(GL_TEXTURE_2D, 0));
	}
}