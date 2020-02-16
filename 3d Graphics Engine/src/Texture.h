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
		Texture(const std::string& path, const std::string& directory = "", const std::string& type = "");
		~Texture() = default;

		void Bind(unsigned int slot = 0);
		void Unbind();

		inline const std::string& GetPath() const { return path; }
		inline const std::string& GetType() const { return type; }

	private:
		void LoadFromFile(const std::string& path, const std::string& directory = "");
	};
}