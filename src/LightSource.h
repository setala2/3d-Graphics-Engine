#pragma once
#include "Drawable.h"

namespace as3d
{
	class LightSource : public as3d::Drawable
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

	public:
		LightSource(Model* model);
		~LightSource() = default;

		void DrawControlWindow(const char* title);

		inline const glm::vec3& GetAmbient() const { return ambient; }
		inline const glm::vec3& GetDiffuse() const { return diffuse; }
		inline const glm::vec3& GetSpecular() const { return specular; }

	/*
	private:
		void Update();
	*/
	};
}