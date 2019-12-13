#include "Renderer.h"

namespace as3d
{
	Renderer::Renderer()
		: clearFlags(GL_COLOR_BUFFER_BIT)
	{}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& s) const
	{
		va.Bind();
		ib.Bind();
		s.Bind();

		glCheckError(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetType(), NULL));
	}

	void Renderer::Clear() const 
	{
		glCheckError(glClear(clearFlags));
	}

	void Renderer::SetClearColor(float r, float g, float b, float a) const
	{
		glCheckError(glClearColor(r, g, b, a));
	}

	void Renderer::EnableBackFaceCulling(bool enable) const
	{
		if (enable)
		{
			glCheckError(glEnable(GL_CULL_FACE));
		}
		else
		{
			glCheckError(glDisable(GL_CULL_FACE));
		}
	}

	void Renderer::EnableDepthTesting(bool enable, GLenum depthFunction)
	{
		SetFlag(GL_DEPTH_BUFFER_BIT, enable);
		if (enable)
		{
			glCheckError(glEnable(GL_DEPTH_TEST));
			glCheckError(glDepthFunc(depthFunction));
		}
		else
		{
			glCheckError(glDisable(GL_DEPTH_TEST));
		}
	}

	void Renderer::SetFlag(GLbitfield flag, bool set)
	{
		if (set)
		{
			clearFlags |= flag;
		}
		else
		{
			clearFlags &= ~(flag);
		}
	}

}
