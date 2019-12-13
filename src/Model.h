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

		void DrawControlWindow(const char* title);
		glm::mat4 GetModelMatrix() const;

		inline unsigned int GetIndexCount() const { return mesh->indexBuffer->GetCount(); };
		inline GLenum GetIndexType() const { return mesh->indexBuffer->GetType(); };

	private:
		void Update();
		void UpdatePosition();
		void UpdateRotation();
		void UpdateScaling();
	};
}