#include "Model.h"

namespace as3d
{
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

	void Model::DrawControlWindow()
	{
		ImGui::Begin("Cube controls");
		if (ImGui::SliderFloat3("position", translation, -10.0f, 10.0f))
			UpdatePosition();
		if (ImGui::SliderFloat3("rotation", rotation, -180.0f, 180.0f))
			UpdateRotation();
		if (ImGui::SliderFloat3("scale", scaling, 0.25f, 4.0f))
			UpdateScaling();
		ImGui::End();
	}

	glm::mat4 Model::GetModelMatrix() const
	{
		return translationMatrix * rotationMatrix * scalingMatrix;
	}

	unsigned int Model::GetIndexCount() const
	{
		return mesh->indexBuffer->GetCount();
	}

	GLenum Model::GetIndexType() const
	{
		return mesh->indexBuffer->GetType();
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
	}

	void Model::UpdateRotation()
	{
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(-1.0, 0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[2]), glm::vec3(0, 0, -1.0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[1]), glm::vec3(0, -1.0, 0));
	}

	void Model::UpdateScaling()
	{
		scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaling[0], scaling[1], scaling[2]));
	}

}