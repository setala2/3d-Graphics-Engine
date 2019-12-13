#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Model.h"
#include "Gldebug.h"
#include "imgui.h"

namespace as3d
{
	class Renderer
	{
		GLbitfield clearFlags;
		bool wireframe;
	public:
		Renderer();

		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& s) const;
		void Draw(const Model& m) const;
		void Clear() const;

		void DrawControlWindow();

		void SetClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) const;
		void EnableBackFaceCulling(bool enable) const;
		void EnableDepthTesting(bool enable, GLenum depthFunction = GL_LESS);
		void EnableWireFrame(bool enable);
		void ToggleWireFrame();

	private:
		void SetFlag(GLbitfield flag, bool set);
	};
}