#include "Model.h"
#include "Gldebug.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace as3d
{
	Mesh::Mesh(const Model* model)
	{
	}

	void Mesh::Draw(const Shader& shader) const
	{
		vao->Bind();
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetType(), NULL);
	}

	Node::Node(const Model* model, const glm::mat4& transform)
		: accumulatedTransform(transform)
	{
	}

	void Node::Draw(const Shader& shader, const glm::mat4& transform) const
	{
		// Draw all of this node's meshes with the current transform
		shader.SetMatrix4("model", accumulatedTransform * transform);
		for (auto& mesh : meshes)
			mesh->Draw(shader);

		// Draw the child nodes
		for (auto& child : children)
			child->Draw(shader, transform);
	}

	void Model::ParseMesh(const aiMesh& mesh)
	{
	}

	void Model::ParseNode(const aiNode& node)
	{
	}

	Model::Model(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		meshes.reserve(scene->mNumMeshes);
		for (std::size_t i = 0; i < scene->mNumMeshes; ++i)
		{
			ParseMesh(*scene->mMeshes[i]);
		}
	}

	void Model::Draw(const Shader& shader) const
	{
		shader.Bind();
		root->Draw(shader, glm::mat4(1.0f));
	}
}
