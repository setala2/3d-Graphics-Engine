#pragma once
#include "Model.h"

namespace as3d
{
	class LightModel : public as3d::Model
	{
		float lightColor[3];
		glm::vec3 lightVector;
		float ambientIntensity;
	public:
		LightModel(Mesh* mesh, Shader* shader);
		~LightModel() = default;

		void DrawControlWindow(const char* title);

		inline glm::vec3 GetColor() const { return lightVector; }
		inline float GetAmbientIntensity() const { return ambientIntensity; }

	private:
		void UpdateColor();
		void Update();
	};
}