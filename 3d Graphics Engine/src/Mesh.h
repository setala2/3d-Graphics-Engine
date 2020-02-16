#pragma once

#include "Gldebug.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

#include <vector>
#include <string>

// My take on the example at https://learnopengl.com/Model-Loading/Mesh
// I'll likely rewrite this later, and make it use our existing buffer/vertex array classes

namespace as3d
{

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	/*struct Texture
	{
		GLuint handle;
		std::string type;
		std::string path;

		void Bind(unsigned int slot) const;
	};*/

	class Mesh
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		VertexBuffer vbo;
		IndexBuffer ibo;
		VertexArray vao;

	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
		void Draw(const Shader& shader);

	private:
		void Init();
	};

}