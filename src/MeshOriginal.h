#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"

namespace as3d
{
	class Mesh
	{
		friend class Model;

		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;

	public:
		Mesh(VertexArray* va, IndexBuffer* ib);

		void Bind() const;
		void Unbind() const;
	};
}