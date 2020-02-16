#include "IndexBuffer.h"

namespace as3d 
{

	IndexBuffer::IndexBuffer(const unsigned int* data, std::size_t count)
		: type(GL_UNSIGNED_INT), count(count)
	{
		glCheckError(glGenBuffers(1, &handle));
		Bind();
		glCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
		Unbind();
	}

	IndexBuffer::IndexBuffer()
		: type(GL_UNSIGNED_INT)
	{
		glCheckError(glGenBuffers(1, &handle));
	}

	IndexBuffer::~IndexBuffer()
	{
		glCheckError(glDeleteBuffers(1, &handle));
	}

	void IndexBuffer::Bind() const
	{
		glCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	}

	void IndexBuffer::Unbind() const
	{
		glCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::SetData(const unsigned int* data, std::size_t count)
	{
		this->count = count;
		glCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

}