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
#include "Renderer.h"
#include "Skybox.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

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

	
	as3d::Model nanoSuit("res/models/nanosuit/nanosuit.obj");
	as3d::Shader shaderNanoSuit("res/shaders/vertex_assimp.glsl", "res/shaders/fragment_assimp.glsl");
	as3d::Model light("res/models/cube.obj");
	as3d::Shader shaderLight("res/shaders/vertex.glsl", "res/shaders/frag.glsl");
	

	std::vector<std::string> skyboxFiles
	{
		"res/textures/skyboxes/mr_02/mr_02rt.jpg",
		"res/textures/skyboxes/mr_02/mr_02lf.jpg",
		"res/textures/skyboxes/mr_02/mr_02up.jpg",
		"res/textures/skyboxes/mr_02/mr_02dn.jpg",
		"res/textures/skyboxes/mr_02/mr_02ft.jpg",
		"res/textures/skyboxes/mr_02/mr_02bk.jpg"
	};
	as3d::Skybox skybox(skyboxFiles);
	as3d::Shader shaderSkybox("res/shaders/skybox_vertex.glsl", "res/shaders/skybox_frag.glsl");

	as3d::Renderer renderer;
	as3d::Camera camera(glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 50.0f));

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		shaderSkybox.Bind();
		shaderSkybox.SetMatrix4("projection", camera.GetProjectionMatrix());
		shaderSkybox.SetMatrix4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
		skybox.Draw(shaderSkybox);
		
		shaderNanoSuit.Bind();
		shaderNanoSuit.SetMatrix4("projection", camera.GetProjectionMatrix());
		shaderNanoSuit.SetMatrix4("view", camera.GetViewMatrix());
		shaderNanoSuit.SetMatrix3("normalMatrix", glm::inverseTranspose(nanoSuit.GetModelMatrix()));
		shaderNanoSuit.SetVector3("cameraPos", camera.GetPosition());
		shaderNanoSuit.SetVector3("lightPos", light.GetPosition());
		nanoSuit.Draw(shaderNanoSuit);
	
		glm::mat4 lightMVP = camera.GetViewProjectionMatrix() * light.GetModelMatrix();
		shaderLight.Bind();
		shaderLight.SetMatrix4("mvp", lightMVP);
		light.Draw(shaderLight);
		

		imgui.BeginFrame();
		camera.DrawControlWindow("camera");
		nanoSuit.DrawControlWindow("model");
		light.DrawControlWindow("light");
		renderer.DrawControlWindow("renderer");
		imgui.EndFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}