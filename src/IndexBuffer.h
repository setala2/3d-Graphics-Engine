#pragma once

#include "Gldebug.h"
#include <cstddef>

namespace as3d
{
	class IndexBuffer
	{
		GLuint handle;
		GLenum type;
		unsigned int count;

	public:
		IndexBuffer(const unsigned int* data, std::size_t count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline GLenum GetType() const { return type; }
		inline unsigned int GetCount() const { return count; }
	};
}