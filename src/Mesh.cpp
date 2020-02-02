#include "Mesh.h"

#include <cstddef>

namespace as3d
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
		: vertices(vertices), indices(indices), textures(textures)
	{
		Init();
	}

	void Mesh::Draw(const Shader& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		for (unsigned int i = 0; i < textures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.SetInt(name + number, i);
			glCheckError(glBindTexture(GL_TEXTURE_2D, textures[i].handle));
		}
		glCheckError(glBindVertexArray(vao));
		glCheckError(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
		glCheckError(glBindVertexArray(0));

		glCheckError(glActiveTexture(GL_TEXTURE0));
	}

	void Mesh::Init()
	{
		// Create the vertex array and the buffers
		glCheckError(glGenVertexArrays(1, &vao));
		glCheckError(glGenBuffers(1, &vbo));
		glCheckError(glGenBuffers(1, &ibo));

		glCheckError(glBindVertexArray(vao));
		glCheckError(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		glCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

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