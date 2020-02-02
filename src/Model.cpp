#include "Model.h"
#include "stb_image.h"
#include <iostream>

namespace as3d
{
	Model::Model(const char* path)
	{
		LoadModel(path);
	}

	void Model::LoadModel(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "Assimp error: " << importer.GetErrorString() << std::endl;
			return;
		}

		directory = path.substr(0, path.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex v;
			glm::vec3 vec;

			// Store the positions
			vec.x = mesh->mVertices[i].x;
			vec.y = mesh->mVertices[i].y;
			vec.z = mesh->mVertices[i].z;
			v.Position = vec;

			// Store the normals
			vec.x = mesh->mNormals[i].x;
			vec.y = mesh->mNormals[i].y;
			vec.z = mesh->mNormals[i].z;
			v.Normal = vec;

			// If there are UV:s in the model, store them
			if (mesh->HasTextureCoords(0))
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				v.TexCoords = vec;
			}
			else
				v.TexCoords = { 0.0,0.0 };

			vertices.push_back(v);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			// Go through all of the faces and for each one, push all of the indices to our vector
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j)
				indices.push_back(face.mIndices[j]);
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			// Check if the texture has already been loaded
			bool alreadyLoaded = false;
			for (unsigned int j = 0; j < loadedTextures.size(); ++j)
			{
				if (std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(loadedTextures[j]);
					alreadyLoaded = true;
					break;
				}
			}

			if(!alreadyLoaded)
			{
				Texture texture;
				texture.handle = TextureFromFile(str.C_Str(), directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
			}
		}
		return textures;
	}

	void Model::Draw(Shader shader)
	{
		for (Mesh& m : meshes)
			m.Draw(shader);
	}
	GLuint TextureFromFile(const char* path, const std::string& directory)
	{
		// Mostly copied from https://learnopengl.com/Lighting/Lighting-maps

		unsigned int handle;
		int width, height, nChannels;

		glCheckError(glGenTextures(1, &handle));
		stbi_uc* imageData = stbi_load(path, &width, &height, &nChannels, 0);
		if (imageData)
		{
			GLenum format;
			switch (nChannels)
			{
			case 1: format = GL_RED; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
			default:
				std::cout << "Unknown pixel format: " << nChannels << " channels." << path << '\n';
				stbi_image_free(imageData);
				return 0;
			}

			glCheckError(glBindTexture(GL_TEXTURE_2D, handle));
			glCheckError(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData));

			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
			glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		}
		else
			std::cout << "Failed to load a texture: " << path << '\n';

		stbi_image_free(imageData);
		glCheckError(glBindTexture(GL_TEXTURE_2D, 0));

		return handle;
	}
}