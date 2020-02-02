#pragma once

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

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

		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

	public:
		Model(const char* path);
		void Draw(const Shader& shader);
	};

	GLuint TextureFromFile(const char* path, const std::string& directory);
}