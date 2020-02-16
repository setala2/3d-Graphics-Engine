#pragma once

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "glm/glm.hpp"

#include <vector>
#include <string>

namespace as3d
{
	class Model
	{
	private:
		using Vertex = Mesh::Vertex;

		std::vector<Mesh> meshes;
		std::string directory;
		std::vector<Texture2D> loadedTextures;

		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scaling;

		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scalingMatrix;
		glm::mat4 modelMatrix;

		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<Mesh>& meshes);
		std::vector<Texture2D> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

		void Translate();
		void Rotate();
		void Scale();
		void Update();
		void Reset();

	public:
		Model(const char* path);

		inline const glm::mat4& GetModelMatrix() const { return modelMatrix; }
		inline const glm::vec3& GetPosition() const { return translation; }

		void Draw(const Shader& shader);
		void DrawControlWindow(const char* title);
	};

}