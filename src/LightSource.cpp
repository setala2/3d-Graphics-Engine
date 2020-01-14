#include "LightSource.h"

namespace as3d
{
	LightSource::LightSource(Model* model)
		: Drawable(model), ambient(0.2f, 0.2f, 0.2f), diffuse(0.5f, 0.5f, 0.5f),
		specular(1.0f, 1.0f, 1.0f)
	{
		drawMaterialControls = false;	// Just going to use the hard coded white color in the shader
	}

	void LightSource::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);
		DrawDrawableControls();
		ImGui::SliderFloat3("ambient", &ambient[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("diffuse", &diffuse[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("specular", &specular[0], 0.0f, 1.0f);
		ImGui::End();
	}

	/*
	void LightSource::Update()
	{
		Model::Update();
	}
	*/
}