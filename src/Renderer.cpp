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
}