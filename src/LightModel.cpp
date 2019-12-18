#include "LightModel.h"

namespace as3d
{
	LightModel::LightModel(Mesh* mesh, Shader* shader)
		: Model(mesh, shader), ambient(0.2f, 0.2f, 0.2f), diffuse(0.5f, 0.5f, 0.5f),
		specular(1.0f, 1.0f, 1.0f), shineExponent(5)
	{	}

	void LightModel::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);
		DrawModelControls();
		ImGui::SliderFloat3("ambient", &ambient[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("diffuse", &diffuse[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("specular", &specular[0], 0.0f, 1.0f);
		ImGui::SliderInt("shininess (2^n)", &shineExponent, 0, 8);
		ImGui::End();
	}

	/*
	void LightModel::Update()
	{
		Model::Update();
	}
	*/
}