#include "Mesh.h"
#include "BufferLayout.h"

#include <cstddef>

namespace as3d
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture2D>& textures)
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
			std::string number;
			std::string name = textures[i].GetType();
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.SetInt("mat." + name + number, i);
			textures[i].Bind(i);
		}
		vao.Bind();
		glCheckError(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
		vao.Unbind();
	}

	void Mesh::Init()
	{
		vao.Bind();
		vbo.Bind();
		ibo.Bind();

		// Fill the buffers
		vbo.SetData(reinterpret_cast<float*>(vertices.data()), vertices.size() * sizeof(Vertex));
		ibo.SetData(indices.data(), indices.size());

		// Set up the layout
		BufferLayout layout;
		layout.Push<float>(3); // Position
		layout.Push<float>(3); // Normal
		layout.Push<float>(2); // UV

		vao.AddBuffer(vbo, layout);
		vao.Unbind();
	}

}