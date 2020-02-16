#pragma once

#include "Texture2D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Shader.h"

#include <vector>
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

	private:
		// Terrain generation code is a modified version of this YouTube tutorial
		// https://www.youtube.com/watch?v=yNYwZMmgTJk

		void Generate();

		static constexpr float size = 800;
		static constexpr int verticesPerRow = 128;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		as3d::Texture2D texture;
		as3d::VertexArray vao;
		as3d::VertexBuffer vbo;
		as3d::IndexBuffer ibo;
	};
}
