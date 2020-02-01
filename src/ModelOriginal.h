#pragma once

#include "MeshOriginal.h"
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
		friend class Drawable;
	protected:
		Mesh* mesh;
		Shader* shader;
		Material material;

	public:
		Model(Mesh* m, Shader* s);
		virtual ~Model() = default;

		void Bind() const;
		void Unbind() const;

		inline const Material& GetMaterial() const { return material; }
		
		inline unsigned int GetIndexCount() const { return mesh->indexBuffer->GetCount(); }
		inline GLenum GetIndexType() const { return mesh->indexBuffer->GetType(); }

	};
}