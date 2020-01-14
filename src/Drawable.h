#pragma once

#include "Gldebug.h"
#include "glm/glm.hpp"
#include "Model.h"

namespace as3d
{
	class Drawable
	{
		Model* model;

		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scalingMatrix;

		glm::mat4 modelMatrix;

		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scaling;

	public:
		Drawable(Model* model);
		virtual ~Drawable() = default;

		void Bind() const;
		void Unbind() const;

		inline const glm::mat4& GetModelMatrix() const { return modelMatrix; }
		inline const glm::vec3& GetPosition() const { return translation; }
		inline const Model* GetModel() const { return model; }

		void DrawControlWindow(const char* title);

		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 pos);
		void SetRotation(float u, float v, float w);
		void SetRotation(glm::vec3 rot);
		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);
		void SetScale(float scale);

	protected:
		// Draws the controls of the drawable class to an existing window.
		// Does not call imgui begin or end.
		void DrawDrawableControls();

		virtual void Update();
		void UpdatePosition();
		void UpdateRotation();
		void UpdateScaling();

		bool drawMaterialControls = true;
	};
}