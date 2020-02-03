#include "GL/glew.h"

#include "GlfwManager.h"
#include "ImguiManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Camera.h"
#include "Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

// #include "Objloader/OBJ_Loader.h"

#include <vector>
#include <cmath>

int main()
{
	GlfwManager glfwManager;

	constexpr unsigned int windowWidth = 1600;
	constexpr unsigned int windowHeight = 900;
	constexpr float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Test window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	ImguiManager imgui(window);

	glewInit();

	/////////////////////////////
	//
	// Testing out Assimp
	//
	/////////////////////////////

	glEnable(GL_DEPTH_TEST);
	as3d::Shader shader("src/shaders/vertex_assimp.glsl", "src/shaders/fragment_assimp.glsl");
	as3d::Model model("src/models/nanosuit/nanosuit.obj");

	as3d::Camera camera(glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 50.0f));


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Bind();
		shader.SetMatrix4("projection", camera.GetProjectionMatrix());
		shader.SetMatrix4("view", camera.GetViewMatrix());
		shader.SetVector3("cameraPos", camera.GetPosition());
		auto modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		shader.SetMatrix4("model", modelMatrix);

		model.Draw(shader);

		imgui.BeginFrame();
		camera.DrawControlWindow("camera");
		model.DrawControlWindow("model");
		imgui.EndFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}