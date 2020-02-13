#pragma once
#include "Gldebug.h"
#include "VertexBuffer.h"

namespace as3d
{
struct BufferLayout;

	class VertexArray
	{
		GLuint handle;
		unsigned int nextIndex;

	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);
	};
}