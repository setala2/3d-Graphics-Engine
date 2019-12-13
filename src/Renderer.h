#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Gldebug.h"

namespace as3d
{
	class Renderer
	{
	public:
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& s) const;
		void Clear(GLbitfield flags) const;
	};
}