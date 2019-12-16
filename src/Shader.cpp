#include "Shader.h"
#include <vector>
#include <string>
#include <fstream>

namespace as3d
{
	Shader::Shader(const char* vertexFile, const char* fragmentFile)
	{
		Compile(vertexFile, fragmentFile);
	}

	Shader::~Shader()
	{
		glCheckError(glDeleteProgram(handle));
	}

	void Shader::Bind() const
	{
		glCheckError(glUseProgram(handle));
	}

	void Shader::Unbind() const
	{
		glCheckError(glUseProgram(0));
	}

	void Shader::SetVector3(const std::string& name, const glm::vec3& vector) const
	{
		glCheckError(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
	}

	void Shader::SetVector3(const std::string& name, float x, float y, float z) const
	{
		glCheckError(glUniform3f(GetUniformLocation(name), x, y, z));
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		glCheckError(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetMatrix4(const std::string& name, const glm::mat4& matrix) const
	{
		glCheckError(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &(matrix[0][0])));
	}

	void Shader::SetMatrix3(const std::string& name, const glm::mat3& matrix) const
	{
		glCheckError(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &(matrix[0][0])));
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glCheckError(glUniform1i(GetUniformLocation(name), value));
	}

	GLint Shader::GetUniformLocation(const std::string& name) const
	{
		if (uniformCache.find(name) != uniformCache.end())
			return uniformCache[name];

		GLint uniform = glCheckError(glGetUniformLocation(handle, name.c_str()));
		uniformCache[name] = uniform;
		return uniform;
	}

	void Shader::Compile(const char* vertexFile, const char* fragmentFile)
	{
		// Mostly copied from https://www.khronos.org/opengl/wiki/Shader_Compilation
		GLuint vertexShader, fragmentShader;

		// Read our shaders into the appropriate buffers
		std::string vertexSource = ReadFile(vertexFile);
		std::string fragmentSource = ReadFile(fragmentFile);

		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			std::cout << "Vertex Shader compilation error:\n";
			std::cout << infoLog.data();

			// In this simple program, we'll just leave
			return;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			std::cout << "Fragment Shader compilation error:\n";
			std::cout << infoLog.data();

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			std::cout << "Shader linking error:\n";
			std::cout << infoLog.data();

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		this->handle = program;
	}

	std::string Shader::ReadFile(const char* path)
	{
		// Open the file in binary mode with the get pointer at the end of the file
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if (!file)
		{
			std::cout << "Could not find file: " << path << '\n';
			return std::string();
		}
		// Get the size of the file and allocate memory for it
		unsigned int size = static_cast<unsigned int>(file.tellg());
		char* shaderSource = new char[size + 1];
		// Go back to the beginning of the file and read the entire thing to the memory
		file.seekg(0);
		file.read(shaderSource, size);
		shaderSource[size] = 0;	// Remember the null terminator
		file.close();

		// Create a string object and free the allocated memory
		std::string src(shaderSource);
		delete[] shaderSource;
		return src;
	}
}