#pragma once

#include "Gldebug.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <vector>
#include <string>

// My take on the example at https://learnopengl.com/Model-Loading/Mesh

namespace as3d
{
	class Mesh
	{
	private:
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};
		friend class Model;

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
