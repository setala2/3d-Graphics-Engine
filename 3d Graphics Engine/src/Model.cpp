#include "Model.h"
#include "Gldebug.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace as3d
{
	Mesh::Mesh(std::unique_ptr<VertexBuffer>& vbo,
		std::unique_ptr<IndexBuffer>&  ibo,
		std::unique_ptr<VertexArray>&  vao)
		: vbo(std::move(vbo)), ibo(std::move(ibo)), vao(std::move(vao))
	{
	}

	void Mesh::Draw(const Shader& shader) const
	{
		vao->Bind();
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetType(), NULL);
	}

	Node::Node(const glm::mat4& transform)
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
		std::vector<Vertex> vertexData;
		vertexData.reserve(mesh.mNumVertices);
		// Parse the vertex data
		for (std::size_t i = 0; i < mesh.mNumVertices; ++i)
		{
			const auto& aiPos = mesh.mVertices[i];

			// Store the vertex position
			Vertex v;
			v.pos.x = aiPos.x;
			v.pos.y = aiPos.y;
			v.pos.z = aiPos.z;

			// Store vertex normals, if available
			if (mesh.HasNormals())
			{
				const auto& aiNorm = mesh.mNormals[i];
				v.norm.x = aiNorm.x;
				v.norm.y = aiNorm.y;
				v.norm.z = aiNorm.z;
			}
			// If not, fill the normal to 0,0,0
			else
			{
				v.norm = { 0.0f,0.0f,0.0f };
			}

			// Do the same for texture coordinates
			if (mesh.HasTextureCoords(0))
			{
				const auto& aiUV = mesh.mTextureCoords[0][i];
				v.uv.x = aiUV.x;
				v.uv.y = aiUV.y;
			}
			else
			{
				v.uv = { 0.0f, 0.0f };
			}
		}

		std::vector<unsigned int> indexData;
		indexData.reserve((std::size_t)mesh.mNumFaces * 3);
		// Parse the index data
		for (std::size_t i = 0; i < mesh.mNumFaces; ++i)
		{
			const auto& face = mesh.mFaces[i];
			for (std::size_t j = 0; j < face.mNumIndices; ++j)	// face.mNumIndices should be 3, since we triangulate the faces in model constructor
			{
				indexData.push_back(face.mIndices[j]);
			}
		}

		auto vbo = std::make_unique<VertexBuffer>(reinterpret_cast<float*>(vertexData.data()), vertexData.size() * sizeof(Vertex));
		auto ibo = std::make_unique<IndexBuffer>(indexData.data(), indexData.size());
		auto vao = std::make_unique<VertexArray>();

		vao->AddBuffer(*vbo, layout);

		meshes.push_back(std::make_unique<Mesh>(vbo, ibo, vao));
	}

	std::unique_ptr<Node> Model::ParseNode(const aiNode& node)
	{
		return std::make_unique<Node>(glm::mat4(1.0f));
	}

	Model::Model(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		layout.Push<float>(3);	// Vertex position
		layout.Push<float>(3);	// Vertex normal
		layout.Push<float>(2);	// Texture coords

		meshes.reserve(scene->mNumMeshes);
		for (std::size_t i = 0; i < scene->mNumMeshes; ++i)
		{
			ParseMesh(*scene->mMeshes[i]);
		}

		root = ParseNode(*scene->mRootNode);
	}

	void Model::Draw(const Shader& shader) const
	{
		shader.Bind();
		root->Draw(shader, glm::mat4(1.0f));
	}
}
