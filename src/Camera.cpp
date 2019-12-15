#include "Camera.h"
#include "imgui.h"

namespace as3d
{
	Camera::Camera(const glm::mat4& projection)
		:  projection(projection), view(1.0f)
	{
		Reset();
	}

	void Camera::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);
		if (ImGui::SliderFloat3("position", translation, -20.0f, 20.0f))
			UpdateTranslation();
		if (ImGui::SliderFloat3("rotation", rotation, -180.0f, 180.0f))
			UpdateRotation();
		if (ImGui::Button("Reset", ImVec2(100, 30)))
			Reset();
		ImGui::End();
	}

	void Camera::UpdateTranslation()
	{
		translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-translation[0], -translation[1], -translation[2]));
		UpdateViewMatrix();
	}

	void Camera::UpdateRotation()
	{
		rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[2]), glm::vec3(0, 0, 1));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[0]), glm::vec3(1, 0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[1]), glm::vec3(0, 1, 0));
		UpdateViewMatrix();
	}

	void Camera::Update()
	{
		UpdateTranslation();
		UpdateRotation();
	}

	void Camera::Reset()
	{
		SetPosition(0.0f, 0.0f, 5.0f);
		SetRotation(0.0f, 0.0f, 0.0f);
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		translation[0] = x;
		translation[1] = y;
		translation[2] = z;
		UpdateTranslation();
	}

	void Camera::SetRotation(float u, float v, float w)
	{
		rotation[0] = u;
		rotation[1] = v;
		rotation[2] = w;
		UpdateRotation();
	}
}