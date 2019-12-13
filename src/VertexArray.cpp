#include "VertexArray.h"
#include "BufferLayout.h"

namespace as3d
{
	VertexArray::VertexArray()
		: nextIndex(0)
	{
		glCheckError(glGenVertexArrays(1, &handle));
	}

	VertexArray::~VertexArray()
	{
		glCheckError(glDeleteVertexArrays(1, &handle));
	}

	void VertexArray::Bind() const
	{
		glCheckError(glBindVertexArray(handle));
	}

	void VertexArray::Unbind() const
	{
		glCheckError(glBindVertexArray(0));
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& layout)
	{
		Bind();
		vb.Bind();

		const auto& elements = layout.elements;
		unsigned int elementOffset = 0;

		for (; nextIndex < elements.size(); ++nextIndex)
		{
			LayoutElement currentElement = elements[nextIndex];
			glCheckError(glEnableVertexAttribArray(nextIndex));
			glCheckError(glVertexAttribPointer(nextIndex, currentElement.count, currentElement.type, GL_FALSE, layout.stride, (const void*)elementOffset));
			elementOffset += currentElement.count * LayoutElement::GetSizeOf(currentElement.type);
		}

		vb.Unbind();
		Unbind();

	}
}