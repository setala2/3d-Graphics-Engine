#include "Model.h"

namespace as3d
{
	Material::Material()
		: ambient(1.0f, 0.5f, 0.31f),
		diffuse(1.0f, 0.5f, 0.31f),
		specular(1.0f),
		shininess(5)
	{}

	Model::Model(Mesh* m, Shader* s)
		: mesh(m), shader(s)
	{	}

	void Model::Bind() const
	{
		mesh->Bind();
		shader->Bind();
	}

	void Model::Unbind() const
	{
		mesh->Unbind();
		shader->Unbind();
	}

}