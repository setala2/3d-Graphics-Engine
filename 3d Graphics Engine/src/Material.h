#pragma once

#include "Texture2D.h"
#include "Shader.h"

#include <vector>
#include <memory>

namespace as3d
{
	class Material
	{
		friend class Model;

	private:
		std::vector<std::unique_ptr<Texture2D>> diffuseMaps;
		std::vector<std::unique_ptr<Texture2D>> specularMaps;

	public:
		void Bind(const Shader& shader) const;
	};
}