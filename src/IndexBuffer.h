#pragma once

#include "Gldebug.h"

namespace as3d
{
	class IndexBuffer
	{
		GLuint handle;
		GLenum type;
		unsigned int count;

	public:
		IndexBuffer(unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline GLenum GetType() const { return type; }
		inline unsigned int GetCount() const { return count; }
	};
}