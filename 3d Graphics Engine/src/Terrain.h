#pragma once

#include "Texture2D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Shader.h"

#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

namespace as3d
{
	class Terrain
	{
	private:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 TexCoords;
		};

	public:
		Terrain(const char* texturePath);

		void Draw(const Shader& shader);
		inline const glm::mat4& GetModelMatrix() { return modelMatrix; }

	private:
		// Terrain generation code is a modified version of this YouTube tutorial
		// https://www.youtube.com/watch?v=yNYwZMmgTJk

		void Generate();

		static constexpr float size = 800;
		static constexpr int verticesPerRow = 128;
		const float offsetX = -size / 2;
		const float offsetZ = -size / 2;

		glm::mat4 modelMatrix;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		// Will need to rethink how to do this at some point.
		// Now we have to create (and load from file) a new texture object,
		// the vao and buffers, for every terrain object we create.
		Texture2D texture;
		VertexArray vao;
		VertexBuffer vbo;
		IndexBuffer ibo;
	};
}
