#pragma once

#include <cstddef>
#include "Gldebug.h"

namespace as3d {

	class VertexBuffer
	{
		GLuint handle;

	public:
		VertexBuffer(float* data, std::size_t bufferSize);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	};

}