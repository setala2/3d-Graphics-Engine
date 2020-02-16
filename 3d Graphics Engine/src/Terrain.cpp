#include "Terrain.h"

namespace as3d
{
	Terrain::Terrain(const char* texturePath)
		: texture(texturePath)
	{
		vertices.reserve(verticesPerRow * verticesPerRow);
		indices.reserve(6 * (verticesPerRow - 1) * (verticesPerRow - 1));
		Generate();
	}

	void Terrain::Generate()
	{
		for(std::size_t z = 0; z < verticesPerRow; ++z)
		{
			for (std::size_t x = 0; x < verticesPerRow; ++x)
			{
				//////////////////////////////////////
				// Create and store the vertex data
				//////////////////////////////////////
				
				glm::vec3 pos;
				pos.x = static_cast<float>(x) / (static_cast<float>(verticesPerRow) - 1) * size;
				pos.y = 0;
				pos.z = static_cast<float>(z) / (static_cast<float>(verticesPerRow) - 1) * size;

				glm::vec3 normals(0.0f, 1.0f, 0.0f);

				glm::vec2 uvs;
				uvs.x = static_cast<float>(x) / (static_cast<float>(verticesPerRow) - 1);
				uvs.y = static_cast<float>(z) / (static_cast<float>(verticesPerRow) - 1);

				vertices.push_back({ pos, normals, uvs });

				//////////////////////////////////////
				// Create and store the index data
				//////////////////////////////////////

				if (x == verticesPerRow - 1 || z == verticesPerRow - 1)
					continue;

				unsigned int topLeft = z * verticesPerRow + x;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = (z + 1) * verticesPerRow + x;
				unsigned int bottomRight = bottomLeft + 1;

				indices.push_back(topLeft);
				indices.push_back(bottomLeft);
				indices.push_back(topRight);
				indices.push_back(topRight);
				indices.push_back(bottomLeft);
				indices.push_back(bottomRight);
			}
		}
	}
}
