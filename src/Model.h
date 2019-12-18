#pragma once

#include "Mesh.h"
#include "Shader.h"

#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace as3d
{
	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		int shininess;

		Material();
	};

	class Model
	{
	protected:
		Mesh* mesh;
		Shader* shader;
		Material material;

		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scalingMatrix;

		float translation[3];
		float rotation[3];
		float scaling[3];

		bool useMaterial = true;

	public:
		Model(Mesh* m, Shader* s);
		virtual ~Model() = default;

		void Bind() const;
		void Unbind() const;

		void DrawControlWindow(const char* title);
		glm::mat4 GetModelMatrix() const;
		glm::vec3 GetPosition() const;
		const Material& GetMaterial() const;

		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 pos);
		void SetRotation(float u, float v, float w);
		void SetRotation(glm::vec3 rot);
		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);
		void SetScale(float scale);

		inline unsigned int GetIndexCount() const { return mesh->indexBuffer->GetCount(); };
		inline GLenum GetIndexType() const { return mesh->indexBuffer->GetType(); };

	protected:
		// Draws the controls of the model class to an existing window.
		// Does not call imgui begin or end.
		void DrawModelControls();

		virtual void Update();
		void UpdatePosition();
		void UpdateRotation();
		void UpdateScaling();
	};
}