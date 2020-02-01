#include "Mesh.h"

#include <cstddef>

namespace as3d
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
		: vertices(vertices), indices(indices), textures(textures)
	{
		Init();
	}

	void Mesh::Draw(Shader shader)
	{
		// Implement later
	}

	void Mesh::Init()
	{
		// Create the vertex array and the buffers
		glCheckError(glGenVertexArrays(1, &vao));
		glCheckError(glGenBuffers(1, &vbo));
		glCheckError(glGenBuffers(1, &ibo));

		glCheckError(glBindVertexArray(vao));
		glCheckError(glBindBuffer(GL_ARRAY_BUFFER, vbo));

		// Fill the buffers
		glCheckError(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
		glCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));

		// Set up the layout
		glCheckError(glEnableVertexAttribArray(0));
		glCheckError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL));

		glCheckError(glEnableVertexAttribArray(1));
		glCheckError(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)));

		glCheckError(glEnableVertexAttribArray(2));
		glCheckError(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords)));

		glCheckError(glBindVertexArray(0));
	}
}