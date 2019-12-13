#pragma once
#include "Gldebug.h"
#include <unordered_map>
#include <string>

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

		GLint GetUniformLocation(const std::string& name);

	private:
		void Compile(const char* vertexFile, const char* fragmentFile);
		std::string ReadFile(const char* path);

		std::unordered_map<std::string, GLint> uniformCache;
	};
}