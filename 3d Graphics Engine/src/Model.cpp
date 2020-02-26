#include "Model.h"
#include "Gldebug.h"
#include "ImguiManager.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <glm/gtc/matrix_transform.hpp>

namespace as3d
{
	/////////////////////////////////////////////////////
	//
	//			Mesh
	//
	/////////////////////////////////////////////////////

	Mesh::Mesh(std::unique_ptr<VertexBuffer>& vbo,
		std::unique_ptr<IndexBuffer>&  ibo,
		std::unique_ptr<VertexArray>&  vao,
		const Material* materialPtr)
		: material(materialPtr), vbo(std::move(vbo)), ibo(std::move(ibo)), vao(std::move(vao))
	{
	}

	void Mesh::Draw(const Shader& shader) const
	{
		vao->Bind();
		ibo->Bind();
		material->Bind(shader);
		glCheckError(glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetType(), NULL));
	}

	/////////////////////////////////////////////////////
	//
	//			Node
	//
	/////////////////////////////////////////////////////

	void Node::Translate()
	{
		translationMatrix = glm::translate(parentTransform, translation);
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

	void Node::Rotate()
	{
		rotationMatrix = glm::mat4_cast(orientation);
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
		prevAngles = eulerAngles;
	}

	void Node::Rotate(glm::vec3 axis)
	{
		// Let the angle be the difference between this and last frame.
		// The dot product takes the correct value from the vector, since the axis has two 0 components and one 1 component.
		float angle = glm::dot((prevAngles - eulerAngles), axis);
		angle = glm::radians(angle);

		// Calculate the local rotation quaternion
		glm::quat local;
		local.w = std::cosf(angle / 2);
		local.x = axis.x * std::sinf(angle / 2);
		local.y = axis.y * std::sinf(angle / 2);
		local.z = axis.z * std::sinf(angle / 2);

		// Multiply with the local rotation with the current orientation to get the new orientation
		orientation = local * orientation;
		Rotate();
	}

	void Node::Scale()
	{
		scalingMatrix = glm::scale(parentTransform, scaling);
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

	void Node::Update()
	{
		Scale();
		Rotate();
		Translate();
	}

	void Node::Reset()
	{
		translation = glm::vec3(0.0f);
		orientation = glm::quat(1,0,0,0);
		eulerAngles = glm::vec3(0.0f);
		scaling = glm::vec3(1.0f);
		Update();
	}

	void Node::DrawControls()
	{
		if (ImGui::TreeNode(name.c_str()))
		{
			if (ImGui::DragFloat3("position", &translation[0], 0.1f, 0, 0, "%.1f"))
				Translate();
			if (ImGui::DragFloat("x rotation", &eulerAngles[0], rotationSpeed, 0, 0, "%.1f"))
				Rotate(glm::vec3(1, 0, 0));
			if (ImGui::DragFloat("y rotation", &eulerAngles[1], rotationSpeed, 0, 0, "%.1f"))
				Rotate(glm::vec3(0, 1, 0));
			if (ImGui::DragFloat("z rotation", &eulerAngles[2], rotationSpeed, 0, 0, "%.1f"))
				Rotate(glm::vec3(0, 0, 1));
			ImGui::SliderFloat("rotation speed", &rotationSpeed, 0.1f, 3.0f, "%.1f");
			if (ImGui::Button("Reset"))
				Reset();
			for (const auto& child : children)
				child->DrawControls();

			ImGui::TreePop();
		}

	}

	Node::Node(std::vector<const Mesh*> meshes, const glm::mat4& transform, const std::string& name)
		: meshes(std::move(meshes)), parentTransform(transform), modelMatrix(transform), name(name)
	{
	}

	void Node::Draw(const Shader& shader, const glm::mat4& accumulatedTransform) const
	{
		// Add this node's transform to the accumulated transform
		const glm::mat4 thisTransform = accumulatedTransform * modelMatrix;

		// Draw all of this node's meshes with the current transform
		shader.SetMatrix4("modelMatrix", thisTransform);
		shader.SetMatrix3("normalMatrix", glm::mat3(thisTransform));
		for (auto& mesh : meshes)
			mesh->Draw(shader);

		// Draw the child nodes
		for (auto& child : children)
			child->Draw(shader, thisTransform);
	}

	/////////////////////////////////////////////////////
	//
	//			Model
	//
	/////////////////////////////////////////////////////

	Model::Model(const std::string& path)
	{
		directory = path.substr(0, path.find_last_of('/'));

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		layout.Push<float>(3);	// Vertex position
		layout.Push<float>(3);	// Vertex normal
		layout.Push<float>(2);	// Texture coords

		// Parse all of the materials
		for (std::size_t i = 0; i < scene->mNumMaterials; ++i)
		{
			ParseMaterial(*scene->mMaterials[i]);
		}

		// Parse all of the meshes
		meshes.reserve(scene->mNumMeshes);
		for (std::size_t i = 0; i < scene->mNumMeshes; ++i)
		{
			ParseMesh(*scene->mMeshes[i]);
		}

		// Parse all of the nodes
		root = ParseNode(*scene->mRootNode);
	}

	void Model::Draw(const Shader& shader) const
	{
		shader.Bind();
		root->Draw(shader, glm::mat4(1.0f));
	}

	void Model::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);
		root->DrawControls();
		ImGui::End();
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
			vertexData.push_back(v);
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
		auto ibo = std::make_unique<IndexBuffer>(indexData.data(), static_cast<GLsizei>(indexData.size()));
		auto vao = std::make_unique<VertexArray>();

		vao->AddBuffer(*vbo, layout);

		const Material* materialPtr = materials[mesh.mMaterialIndex].get();

		meshes.push_back(std::make_unique<Mesh>(vbo, ibo, vao, materialPtr));
	}

	std::unique_ptr<Node> Model::ParseNode(const aiNode& node)
	{
		// Store references to all of this node's meshes
		std::vector<const Mesh*> nodeMeshes;
		nodeMeshes.reserve(node.mNumMeshes);
		for (std::size_t i = 0; i < node.mNumMeshes; ++i)
		{
			nodeMeshes.push_back(meshes[node.mMeshes[i]].get());
		}

		// Apparently assimp stores the matrix in row major - and glm in column major order, so we'll transpose the matrix
		glm::mat4 nodeTransform = glm::transpose(*reinterpret_cast<const glm::mat4*>(&node.mTransformation));
		
		// Create the new node
		auto newNode = std::make_unique<Node>(nodeMeshes, nodeTransform, node.mName.C_Str());

		// Create the children of the new node recursively
		newNode->children.reserve(node.mNumChildren);
		for (std::size_t i = 0; i < node.mNumChildren; ++i)
		{
			newNode->children.push_back(ParseNode(*node.mChildren[i]));
		}

		return newNode;
	}

	void Model::ParseMaterial(const aiMaterial& mat)
	{
		// Could load the different textures in a nested for loop once we start supporting more complex materials

		auto newMaterial = std::make_unique<Material>();
		newMaterial->diffuseMaps.reserve(mat.GetTextureCount(aiTextureType_DIFFUSE));
		newMaterial->specularMaps.reserve(mat.GetTextureCount(aiTextureType_SPECULAR));

		for (unsigned int i = 0; i < mat.GetTextureCount(aiTextureType_DIFFUSE); ++i)
		{
			aiString path;
			mat.GetTexture(aiTextureType_DIFFUSE, i, &path);
			newMaterial->diffuseMaps.push_back(std::make_unique<Texture2D>(path.C_Str(), directory, "texture_diffuse"));
		}
		for (unsigned int i = 0; i < mat.GetTextureCount(aiTextureType_SPECULAR); ++i)
		{
			aiString path;
			mat.GetTexture(aiTextureType_SPECULAR, i, &path);
			newMaterial->specularMaps.push_back(std::make_unique<Texture2D>(path.C_Str(), directory, "texture_specular"));
		}

		materials.push_back(std::move(newMaterial));
	}
}
