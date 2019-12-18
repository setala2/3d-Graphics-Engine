#pragma once
#include "Model.h"

namespace as3d
{
	class LightModel : public as3d::Model
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

	public:
		LightModel(Mesh* mesh, Shader* shader);
		~LightModel() = default;

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