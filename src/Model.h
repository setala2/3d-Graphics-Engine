#pragma once

#include "Mesh.h"
#include "Shader.h"

#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace as3d
{
	class Model
	{
		Mesh* mesh;
		Shader* shader;

		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scalingMatrix;

		float translation[3];
		float rotation[3];
		float scaling[3];

	public:
		Model(Mesh* m, Shader* s);

		void Bind() const;
		void Unbind() const;

		void DrawControlWindow();
		glm::mat4 GetModelMatrix() const;

		unsigned int GetIndexCount() const;
		GLenum GetIndexType() const;

	private:
		void Update();
		void UpdatePosition();
		void UpdateRotation();
		void UpdateScaling();
	};
}