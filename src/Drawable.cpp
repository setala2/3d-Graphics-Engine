#include "Drawable.h"

namespace as3d
{
	Drawable::Drawable(Model* model)
		: model(model), translation{ 0 },
		rotation{ 0 }, scaling{ 1,1,1 }
	{
		Update();
	}

	void Drawable::Bind() const
	{
		model->Bind();
	}

	void Drawable::Unbind() const
	{
		model->Unbind();
	}

	void Drawable::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);
		DrawDrawableControls();
		ImGui::End();
	}

	void Drawable::SetPosition(float x, float y, float z)
	{
		translation[0] = x;
		translation[1] = y;
		translation[2] = z;
		UpdatePosition();
	}

	void Drawable::SetPosition(glm::vec3 pos)
	{
		SetPosition(pos.x, pos.y, pos.z);
	}

	void Drawable::SetRotation(float x, float y, float z)
	{
		rotation[0] = x;
		rotation[1] = y;
		rotation[2] = z;
		UpdateRotation();
	}

	void Drawable::SetRotation(glm::vec3 rot)
	{
		SetRotation(rot.x, rot.y, rot.z);
	}

	void Drawable::SetScale(float x, float y, float z)
	{
		scaling[0] = x;
		scaling[1] = y;
		scaling[2] = z;
		UpdateScaling();
	}

	void Drawable::SetScale(glm::vec3 scale)
	{
		SetScale(scale.x, scale.y, scale.z);
	}

	void Drawable::SetScale(float scale)
	{
		SetScale(scale, scale, scale);
	}

	void Drawable::DrawDrawableControls()
	{
		if (ImGui::SliderFloat3("position", &translation[0], -10.0f, 10.0f))
			UpdatePosition();
		if (ImGui::SliderFloat3("rotation", &rotation[0], -180.0f, 180.0f))
			UpdateRotation();
		if (ImGui::SliderFloat3("scale", &scaling[0], 0.25f, 4.0f))
			UpdateScaling();
		if (drawMaterialControls)
		{
			ImGui::Text("Material");
			ImGui::BeginChild("material");
			ImGui::SliderFloat3("ambient", &(model->material.ambient[0]), 0.0f, 1.0f);
			ImGui::SliderFloat3("diffuse", &(model->material.diffuse[0]), 0.0f, 1.0f);
			ImGui::SliderFloat3("specular", &(model->material.specular[0]), 0.0f, 1.0f);
			ImGui::SliderInt("shininess (2^n)", &(model->material.shininess), 0, 8);
			ImGui::EndChild();
		}
	}

	void Drawable::Update()
	{
		UpdatePosition();
		UpdateRotation();
		UpdateScaling();
	}

	void Drawable::UpdatePosition()
	{
		translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation[0], translation[1], translation[2]));
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

	void Drawable::UpdateRotation()
	{
		rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[1]), glm::vec3(0, -1.0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[0]), glm::vec3(-1.0, 0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[2]), glm::vec3(0, 0, -1.0));
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

	void Drawable::UpdateScaling()
	{
		scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaling[0], scaling[1], scaling[2]));
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

}