#include "Camera.h"
#include "Input.h"

#include <iostream>
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
		ImGui::Text("Control camera with WASDQE and arrow keys");
		ImGui::Text("Position\tx: %f y: %f z: %f", translation[0], translation[1], translation[2]);
		ImGui::Text("Rotation\tx: %f y: %f z: %f", rotation[0], rotation[1], rotation[2]);
		ImGui::SliderFloat("Movement speed", &movementSpeed, 1.0f, 20.0f, "%.1f");
		ImGui::SliderFloat("Rotation speed", &rotationSpeed, 100.0f, 300.0f, "%.1f");
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

	void Camera::UpdateAll()
	{
		UpdateTranslation();
		UpdateRotation();
	}

	void Camera::Reset()
	{
		SetPosition(0.0f, 10.0f, 10.0f);
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

	void Camera::OnUpdate(float deltaTime)
	{
		if (Input::IsKeyPressed(GLFW_KEY_A))
			MoveLeft(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_D))
			MoveRight(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_W))
			MoveForward(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_S))
			MoveBack(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_Q))
			MoveDown(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_E))
			MoveUp(deltaTime);

		if (Input::IsKeyPressed(GLFW_KEY_LEFT))
			RotateLeft(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
			RotateRight(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_UP))
			RotateUp(deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_DOWN))
			RotateDown(deltaTime);
	}

	void Camera::MoveLeft(float deltaTime)
	{
		translation[0] -= std::cosf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		translation[2] -= std::sinf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		UpdateTranslation();
	}

	void Camera::MoveRight(float deltaTime)
	{
		translation[0] += std::cosf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		translation[2] += std::sinf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		UpdateTranslation();
	}

	void Camera::MoveForward(float deltaTime)
	{
		translation[0] += std::sinf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		translation[2] -= std::cosf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		UpdateTranslation();
	}

	void Camera::MoveBack(float deltaTime)
	{
		translation[0] -= std::sinf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		translation[2] += std::cosf(glm::radians(rotation[1])) * movementSpeed * deltaTime;
		UpdateTranslation();
	}

	void Camera::MoveUp(float deltaTime)
	{
		translation[1] += movementSpeed * deltaTime;
		UpdateTranslation();
	}

	void Camera::MoveDown(float deltaTime)
	{
		translation[1] -= movementSpeed * deltaTime;
		UpdateTranslation();
	}

	void Camera::RotateLeft(float deltaTime)
	{
		rotation[1] -= rotationSpeed * deltaTime;
		UpdateRotation();
	}

	void Camera::RotateRight(float deltaTime)
	{
		rotation[1] += rotationSpeed * deltaTime;
		UpdateRotation();
	}

	void Camera::RotateUp(float deltaTime)
	{
		rotation[0] -= rotationSpeed * deltaTime;
		UpdateRotation();
	}

	void Camera::RotateDown(float deltaTime)
	{
		rotation[0] += rotationSpeed * deltaTime;
		UpdateRotation();
	}

}