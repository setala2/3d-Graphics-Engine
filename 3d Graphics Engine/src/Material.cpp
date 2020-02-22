#include "Material.h"

namespace as3d
{
	void Material::Bind(const Shader& shader) const
	{
		int currentSlot = 0;

		for (std::size_t i = 0; i < diffuseMaps.size(); ++i)
		{
			shader.SetInt("mat.texture_diffuse" + std::to_string(i), currentSlot);	// Bind the current texture slot to texture_diffuse1 etc...
			diffuseMaps[i]->Bind(currentSlot++);
		}
		for (std::size_t i = 0; i < specularMaps.size(); ++i)
		{
			shader.SetInt("mat.texture_specular" + std::to_string(i), currentSlot);	
			specularMaps[i]->Bind(currentSlot++);
		}
	}
}