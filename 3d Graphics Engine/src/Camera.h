#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace as3d
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projection);

		void DrawControlWindow(const char* title);
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);

		void OnUpdate(float deltaTime);

		inline glm::mat4 GetViewProjectionMatrix() { return projection * view; };
		inline glm::mat4 GetViewMatrix() { return view; }
		inline glm::mat4 GetProjectionMatrix() { return projection; }
		inline glm::vec3 GetPosition() { return glm::vec3(translation[0], translation[1], translation[2]); }

	private:
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;

		float translation[3];
		float rotation[3];

		glm::mat4 projection;
		glm::mat4 view;

		float movementSpeed = 10.0f;
		float rotationSpeed = 200.0f;

	private:
		inline void UpdateViewMatrix() { view = rotationMatrix * translationMatrix; }

		void UpdateTranslation();
		void UpdateRotation();
		void UpdateAll();
		void Reset();

		void MoveLeft(float deltaTime);
		void MoveRight(float deltaTime);
		void MoveForward(float deltaTime);
		void MoveBack(float deltaTime);
		void MoveUp(float deltaTime);
		void MoveDown(float deltaTime);

		void RotateLeft(float deltaTime);
		void RotateRight(float deltaTime);
		void RotateUp(float deltaTime);
		void RotateDown(float deltaTime);

	};
}