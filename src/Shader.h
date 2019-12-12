#pragma once
#include "Gldebug.h"

namespace as3d
{
	class Shader
	{
		GLuint handle;

	public:
		Shader(const char* vertexFile, const char* fragmentFile);
		~Shader();

		void Bind() const;

		void Unbind() const;

	private:
		void Compile(const char* vertexFile, const char* fragmentFile);
		std::string ReadFile(const char* path);
	};
}