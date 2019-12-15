#include "LightModel.h"

namespace as3d
{
	LightModel::LightModel(Mesh* mesh, Shader* shader)
		: Model(mesh, shader), lightColor{0.8f, 0.36f, 0.1f}, ambientIntensity(0.3f)
	{
		UpdateColor();
	}

	void LightModel::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);
		DrawModelControls();
		if (ImGui::ColorPicker3("light color", lightColor))
			UpdateColor();
		ImGui::SliderFloat("ambient intensity", &ambientIntensity, 0.0f, 1.0f);
		ImGui::End();
	}
	void LightModel::UpdateColor()
	{
		lightVector.r = lightColor[0];
		lightVector.g = lightColor[1];
		lightVector.b = lightColor[2];
	}
	void LightModel::Update()
	{
		Model::Update();
		UpdateColor();
	}
}