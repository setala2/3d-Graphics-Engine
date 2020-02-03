#include "VertexBuffer.h"

namespace as3d {

	VertexBuffer::VertexBuffer(float* data, std::size_t bufferSize)
	{
		glCheckError(glGenBuffers(1, &handle));
		Bind();
		glCheckError(glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW));
		Unbind();
	}

	VertexBuffer::VertexBuffer()
	{
		glCheckError(glGenBuffers(1, &handle));
	}

	VertexBuffer::~VertexBuffer()
	{
		glCheckError(glDeleteBuffers(1, &handle));
	}

	void VertexBuffer::Bind() const
	{
		glCheckError(glBindBuffer(GL_ARRAY_BUFFER, handle));
	}

	void VertexBuffer::Unbind() const
	{
		glCheckError(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::SetData(float* data, std::size_t bufferSize) const
	{
		glCheckError(glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW));
	}

}