#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture2D.h"
#include "BufferLayout.h"
#include "Shader.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace as3d
{
	class Model;

	class Mesh
	{
	private:
		const Texture2D* texture;
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<IndexBuffer>  ibo;
		std::unique_ptr<VertexArray>  vao;

	public:
		Mesh(const Model* model);

		void Draw(const Shader& shader) const;
	};

	class Node
	{
	private:
		std::vector<std::unique_ptr<Node>> children;
		std::vector<std::unique_ptr<Mesh>> meshes;

		glm::mat4 accumulatedTransform;

	public:
		Node(const Model* model);

		void Draw(const Shader& shader, glm::mat4 transform) const;
	};

	class Model
	{
	private:
		std::unique_ptr<Node> root;
		std::vector<std::unique_ptr<Texture2D>> textures;

		BufferLayout layout;

	public:
		Model(const char* path);

		void Draw(const Shader& shader) const;
	};
}