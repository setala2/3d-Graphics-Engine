#pragma once

#include "Texture2D.h"

#include <vector>
#include <glm/glm.hpp>

namespace as3d
{
	class Terrain
	{
	private:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 TexCoords;
		};

	public:
		Terrain(const char* texturePath);

	private:
		// Terrain generation code is a modified version of this YouTube tutorial
		// https://www.youtube.com/watch?v=yNYwZMmgTJk

		void Generate();

		static constexpr float size = 800;
		static constexpr int verticesPerRow = 128;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		as3d::Texture2D texture;
	};
}