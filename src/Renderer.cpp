#include "Renderer.h"

namespace as3d
{
	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& s) const
	{
		va.Bind();
		ib.Bind();
		s.Bind();

		glCheckError(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetType(), NULL));
	}

	void Renderer::Clear(GLbitfield flags) const 
	{
		glCheckError(glClear(flags));
	}

	void Renderer::SetClearColor(float r, float g, float b, float a) const
	{
		glCheckError(glClearColor(r, g, b, a));
	}

	void Renderer::EnableBackFaceCull(bool enable) const
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
}