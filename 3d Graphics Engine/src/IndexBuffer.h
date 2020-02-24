#pragma once

#include "Gldebug.h"
#include <cstddef>

namespace as3d
{
	class IndexBuffer
	{
		GLuint handle;
		GLenum type;
		GLsizei count = 0;

	public:
		IndexBuffer(const unsigned int* data, GLsizei count);
		IndexBuffer();
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
		void SetData(const unsigned int* data, GLsizei count);

		inline GLenum GetType() const { return type; }
		inline GLsizei GetCount() const { return count; }
	};
}