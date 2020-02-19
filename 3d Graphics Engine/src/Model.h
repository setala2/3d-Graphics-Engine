#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture2D.h"
#include "BufferLayout.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include <memory>
#include <vector>

namespace as3d
{
	class Model;

	class Mesh
	{
	private:
		const Texture2D* texture = nullptr;
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
		std::vector<const Mesh*> meshes;

		glm::mat4 accumulatedTransform;

	public:
		Node(const Model* model, const glm::mat4& transform);

		void Draw(const Shader& shader, const glm::mat4& transform) const;
	};

	class Model
	{
	private:
		std::unique_ptr<Node> root;

		// A vector of textures owned by this model. Each mesh has a pointer that 
		// references its texture in this vector.
		std::vector<std::unique_ptr<Texture2D>> textures;
		
		// A vector of meshes owned by this model. Each node references its meshes
		// (that are stored here) via a pointer.
		std::vector<std::unique_ptr<Mesh>> meshes;

		BufferLayout layout;

		void ParseMesh(const aiMesh& mesh);
		void ParseNode(const aiNode& node);

	public:
		Model(const std::string& path);

		void Draw(const Shader& shader) const;
	};
}