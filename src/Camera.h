#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace as3d
{
	class Camera
	{
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;

		float translation[3];
		float rotation[3];

		glm::mat4 projection;
		glm::mat4 view;

	public:
		Camera(const glm::mat4& projection);

		void DrawControlWindow(const char* title);
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);

		inline glm::mat4 GetViewProjectionMatrix() { return projection * view; };

	private:
		inline void UpdateViewMatrix() { view = rotationMatrix * translationMatrix; }

		void UpdateTranslation();
		void UpdateRotation();
		void Update();
		void Reset();

	};
}