#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Shader.h"
#include "Material.h"

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include <memory>
#include <vector>

namespace as3d
{
	class Mesh
	{
	private:
		const Material* material = nullptr;	// All textures are owned by the model instance, this is just a reference
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<IndexBuffer>  ibo;
		std::unique_ptr<VertexArray>  vao;

	public:
		Mesh(std::unique_ptr<VertexBuffer>& vbo,
		std::unique_ptr<IndexBuffer>&  ibo,
		std::unique_ptr<VertexArray>&  vao,
		const Material* materialPtr);
		void Draw(const Shader& shader) const;
	};

	class Node
	{
		friend class Model;
	private:
		std::vector<std::unique_ptr<Node>> children;
		std::vector<const Mesh*> meshes;

		glm::mat4 parentTransform;
		glm::mat4 modelMatrix;

		glm::mat4 translationMatrix = glm::mat4(1.0f);
		glm::mat4 rotationMatrix    = glm::mat4(1.0f);
		glm::mat4 scalingMatrix     = glm::mat4(1.0f);

		glm::vec3 translation = glm::vec3(0.0f);
		glm::vec3 rotation    = glm::vec3(0.0f);
		glm::vec3 scaling     = glm::vec3(0.0f);

		std::string name;

	private:
		void Translate();
		void Rotate();
		void Scale();
		void Update();
		void Reset();
		void DrawControls();	// Should only be called by Model::DrawControlWindow()

	public:
		Node(std::vector<const Mesh*> meshes, const glm::mat4& transform, const std::string& name = "");

		void Draw(const Shader& shader, const glm::mat4& accumulatedTransform) const;
	};
	
	class Model
	{
	public:
		Model(const std::string& path);

		void Draw(const Shader& shader) const;
		void DrawControlWindow(const char* title);

		inline glm::vec3 GetPosition() const { return root->translation; }

	private:
		struct Vertex
		{
			glm::vec3 pos;
			glm::vec3 norm;
			glm::vec2 uv;
		};

		std::unique_ptr<Node> root;

		// A vector of materials owned by this model. Each mesh has a pointer that 
		// references its material in this vector.
		std::vector<std::unique_ptr<Material>> materials;
		
		// A vector of meshes owned by this model. Each node references its meshes
		// (that are stored here) via a pointer.
		std::vector<std::unique_ptr<Mesh>> meshes;

		BufferLayout layout;

		std::string directory;

	private:
		void ParseMesh(const aiMesh& mesh);
		std::unique_ptr<Node> ParseNode(const aiNode& node);
		void ParseMaterial(const aiMaterial& mat);

	};
}
