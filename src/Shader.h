#pragma once
#include "Gldebug.h"
#include "glm/glm.hpp"

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

		void SetMatrix4(const std::string& name, const glm::mat4& matrix) const;
		void SetMatrix3(const std::string& name, const glm::mat3& matrix) const;
		void SetVector3(const std::string& name, const glm::vec3& vector) const;
		void SetVector3(const std::string& name, float x, float y, float z) const;
		void SetFloat(const std::string& name, float value) const;

	private:
		void Compile(const char* vertexFile, const char* fragmentFile);
		std::string ReadFile(const char* path);

		GLint GetUniformLocation(const std::string& name) const;
		mutable std::unordered_map<std::string, GLint> uniformCache;
	};
}