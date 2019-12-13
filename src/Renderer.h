#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Gldebug.h"

namespace as3d
{
	class Renderer
	{
		GLbitfield clearFlags;
	public:
		Renderer();

		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& s) const;
		void Clear() const;

		void SetClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) const;
		void EnableBackFaceCulling(bool enable) const;
		void EnableDepthTesting(bool enable, GLenum depthFunction = GL_LESS);

	private:
		void SetFlag(GLbitfield flag, bool set);
	};
}