#include "Renderer.h"

namespace as3d
{
	Renderer::Renderer()
		: clearFlags(GL_COLOR_BUFFER_BIT), wireframe(false),
		bfc(false), blend(false)
	{
		// Enable depth testing by default
		EnableDepthTesting(true);
	}

	void Renderer::Clear() const 
	{
		glCheckError(glClear(clearFlags));
	}

	void Renderer::DrawControlWindow(const char* title)
	{
		ImGui::Begin(title);

		if (ImGui::Button("Toggle Wireframe"))
			ToggleWireFrame();
		ImGui::SameLine();
		ImGui::Text(wireframe ? on : off);

		if (ImGui::Button("Toggle Culling"))
			ToggleBackFaceCulling();
		ImGui::SameLine();
		ImGui::Text(bfc ? on : off);

		if (ImGui::Button("Toggle Depth testing"))
			ToggleDepthTest();
		ImGui::SameLine();
		ImGui::Text(depthTest ? on : off);

		if (ImGui::Button("Toggle Blending"))
			ToggleBlending();
		ImGui::SameLine();
		ImGui::Text(blend ? on : off);

		ImGui::End();
	}

	void Renderer::SetClearColor(float r, float g, float b, float a) const
	{
		glCheckError(glClearColor(r, g, b, a));
	}

	void Renderer::EnableBackFaceCulling(bool enable)
	{
		bfc = enable;
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
		depthTest = enable;
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

	void Renderer::EnableWireFrame(bool enable)
	{
		wireframe = enable;
		if (enable)
		{
			glCheckError(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		else
		{
			glCheckError(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
	}

	void Renderer::ToggleWireFrame()
	{
		EnableWireFrame(!wireframe);
	}

	void Renderer::ToggleBackFaceCulling()
	{
		EnableBackFaceCulling(!bfc);
	}

	void Renderer::ToggleDepthTest()
	{
		EnableDepthTesting(!depthTest);
	}

	void Renderer::EnableBlending(bool enable, GLenum src, GLenum dest)
	{
		if (enable)
		{
			glCheckError(glEnable(GL_BLEND));
			glCheckError(glBlendFunc(src, dest));
		}
		else
		{
			glCheckError(glDisable(GL_BLEND));
		}
		blend = enable;
	}

	void Renderer::ToggleBlending()
	{
		EnableBlending(!blend);
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
