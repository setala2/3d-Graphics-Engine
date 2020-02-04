#pragma once
#include "Gldebug.h"
#include "imgui.h"

namespace as3d
{
	class Renderer
	{
		GLbitfield clearFlags;
		bool wireframe;
		bool bfc;
		bool depthTest;

		const char* on = "on";
		const char* off = "off";

	public:
		Renderer();

		void Clear() const;

		void DrawControlWindow(const char* title);

		void SetClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) const;
		void EnableBackFaceCulling(bool enable);
		void EnableDepthTesting(bool enable, GLenum depthFunction = GL_LESS);
		void EnableWireFrame(bool enable);
		void ToggleWireFrame();
		void ToggleBackFaceCulling();
		void ToggleDepthTest();	// Can't change the depth function with this

	private:
		void SetFlag(GLbitfield flag, bool set);
	};
}