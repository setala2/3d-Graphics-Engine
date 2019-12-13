#include "Mesh.h"

namespace as3d
{
	Mesh::Mesh(VertexArray* va, IndexBuffer* ib)
		: vertexArray(va), indexBuffer(ib)
	{
	}

	void Mesh::Bind() const
	{
		vertexArray->Bind();
		indexBuffer->Bind();
	}

	void Mesh::Unbind() const
	{
		indexBuffer->Unbind();
		vertexArray->Unbind();
	}
}