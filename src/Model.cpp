#include "Model.h"

namespace as3d
{
	Material::Material()
		: ambient(1.0f, 0.5f, 0.31f),
		diffuse(1.0f, 0.5f, 0.31f),
		specular(1.0f),
		shininess(5)
	{}

	Model::Model(Mesh* m, Shader* s)
		: mesh(m), shader(s), translation{ 0 },
		rotation{ 0 }, scaling{ 1,1,1 }
	{
		Update();
	}

	void Model::Bind() const
	{
		mesh->Bind();
		shader->Bind();
	}

	void Model::Unbind() const
	{
		mesh->Unbind();
		shader->Unbind();
	}

	void Model::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);
		DrawModelControls();
		ImGui::End();
	}

	void Model::SetPosition(float x, float y, float z)
	{
		translation[0] = x;
		translation[1] = y;
		translation[2] = z;
		UpdatePosition();
	}

	void Model::SetPosition(glm::vec3 pos)
	{
		SetPosition(pos.x, pos.y, pos.z);
	}

	void Model::SetRotation(float x, float y, float z)
	{
		rotation[0] = x;
		rotation[1] = y;
		rotation[2] = z;
		UpdateRotation();
	}

	void Model::SetRotation(glm::vec3 rot)
	{
		SetRotation(rot.x, rot.y, rot.z);
	}

	void Model::SetScale(float x, float y, float z)
	{
		scaling[0] = x;
		scaling[1] = y;
		scaling[2] = z;
		UpdateScaling();
	}

	void Model::SetScale(glm::vec3 scale)
	{
		SetScale(scale.x, scale.y, scale.z);
	}

	void Model::SetScale(float scale)
	{
		SetScale(scale, scale, scale);
	}

	void Model::DrawModelControls()
	{
		if (ImGui::SliderFloat3("position", &translation[0], -10.0f, 10.0f))
			UpdatePosition();
		if (ImGui::SliderFloat3("rotation", &rotation[0], -180.0f, 180.0f))
			UpdateRotation();
		if (ImGui::SliderFloat3("scale", &scaling[0], 0.25f, 4.0f))
			UpdateScaling();
		if (useMaterial)
		{
			ImGui::Text("Material");
			ImGui::BeginChild("material");
			ImGui::SliderFloat3("ambient", &material.ambient[0], 0.0f, 1.0f);
			ImGui::SliderFloat3("diffuse", &material.diffuse[0], 0.0f, 1.0f);
			ImGui::SliderFloat3("specular", &material.specular[0], 0.0f, 1.0f);
			ImGui::SliderInt("shininess (2^n)", &material.shininess, 0, 8);
			ImGui::EndChild();
		}
	}

	void Model::Update()
	{
		UpdatePosition();
		UpdateRotation();
		UpdateScaling();
	}

	void Model::UpdatePosition()
	{
		translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation[0], translation[1], translation[2]));
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

	void Model::UpdateRotation()
	{
		rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[1]), glm::vec3(0, -1.0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[0]), glm::vec3(-1.0, 0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[2]), glm::vec3(0, 0, -1.0));
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

	void Model::UpdateScaling()
	{
		scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaling[0], scaling[1], scaling[2]));
		modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

}