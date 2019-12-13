#pragma once

#include "glm/glm.hpp"

namespace as3d
{
	class Camera
	{
		glm::mat4 projection;
		glm::mat4 view;

	public:
		Camera(const glm::mat4& projection);

		inline glm::mat4 GetViewProjectionMatrix() { return projection * view; };
	};
}