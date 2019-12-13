#pragma once
#include "GL/glew.h"
#include <iostream>
#include <vector>
#include <cassert>

namespace as3d
{
	struct LayoutElement
	{
		GLenum type;
		unsigned int count;

		static unsigned int GetSizeOf(GLenum type)
		{
			switch (type)
			{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_BYTE:	return 1;
			}
			assert(false);
			return 0;
		}
	};

	struct  BufferLayout
	{
		std::vector<LayoutElement> elements;
		unsigned int stride = 0;

		template<typename T>
		void Push(unsigned int count)
		{
			std::cout << "Trying to push an unknown type to a layout.\n";
		}

		template<>
		void Push<float>(unsigned int count)
		{
			elements.push_back({ GL_FLOAT, count });
			stride += LayoutElement::GetSizeOf(GL_FLOAT) * count;
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			elements.push_back({ GL_UNSIGNED_BYTE, count });
			stride += LayoutElement::GetSizeOf(GL_UNSIGNED_BYTE) * count;
		}
	};

}