#include "Skybox.h"

namespace as3d
{
	Skybox::Skybox(const std::vector<std::string>& filenames)
		: texture(filenames), vbo(vertices, sizeof(vertices))
	{
		BufferLayout layout;
		layout.Push<float>(3);
		vao.AddBuffer(vbo, layout);
	}

	void Skybox::Draw(const Shader& shader)
	{
		glCheckError(glDepthMask(GL_FALSE));
		texture.Bind();
		shader.Bind();
		vao.Bind();
		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));
		glCheckError(glDepthMask(GL_TRUE));
	}
}