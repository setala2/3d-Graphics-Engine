#include "Camera.h"

namespace as3d
{
	Camera::Camera(const glm::mat4& projection)
		: projection(projection), view(1.0f)
	{}
}