#pragma once

#include "Texture2D.h"

#include <vector>
#include <memory>

namespace as3d
{
	class Material
	{
	private:
		std::vector<std::unique_ptr<Texture2D>> diffuseMaps;
		std::vector<std::unique_ptr<Texture2D>> specularMaps;

	public:

	};
}