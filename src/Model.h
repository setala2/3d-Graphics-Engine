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
		std::vector<Mesh> meshes;
		std::string directory;
		std::vector<Texture> loadedTextures;

		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scaling;

		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scalingMatrix;
		glm::mat4 modelMatrix;

		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

		void Translate();
		void Rotate();
		void Scale();
		void Update();

	public:
		Model(const char* path);
		void Draw(const Shader& shader);
		inline const glm::mat4& GetModelMatrix() const { return modelMatrix; }
		void DrawControlWindow(const char* title);
	};

	static GLuint TextureFromFile(const char* path, const std::string& directory);
}