#pragma once

#include <cstddef>
#include "Gldebug.h"

namespace as3d {

	class VertexBuffer
	{
		GLuint handle;

	public:
		VertexBuffer(const float* data, std::size_t bufferSize);
		VertexBuffer();
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(float* data, std::size_t bufferSize) const;
	};

}