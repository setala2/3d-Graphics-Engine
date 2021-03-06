#include <GL/glew.h>

#include "Window.h"
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
#include "Input.h"
#include "Terrain.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

int main()
{
	constexpr unsigned int windowWidth = 1600;
	constexpr unsigned int windowHeight = 900;
	constexpr float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

	/////////////////////////////////////
	//	Set up GLFW, ImGui and GLEW
	/////////////////////////////////////

	as3d::Window window(windowWidth, windowHeight, "3D Engine");
	window.MakeCurrent();

	ImguiManager imgui(window.GetPointer());

	glewInit();

	////////////////////////////////////
	//	Load the models and shaders
	////////////////////////////////////

	as3d::Model nanoSuit("res/models/nanosuit/nanosuit.obj");
	as3d::Shader shaderNanoSuit("res/shaders/nanosuit_vertex.glsl", "res/shaders/nanosuit_fragment.glsl");
	as3d::Model light("res/models/cube.obj");
	as3d::Shader shaderLight("res/shaders/simple_vertex.glsl", "res/shaders/simple_fragment.glsl");

	////////////////////////////////////////
	//	Load the skybox and its shaders
	////////////////////////////////////////

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
	as3d::Shader shaderSkybox("res/shaders/skybox_vertex.glsl", "res/shaders/skybox_fragment.glsl");

	////////////////////////////////////////
	//	Create the terrain and its shaders
	////////////////////////////////////////

	as3d::Terrain terrain("res/textures/terrain/ground1/ground1.png");
	as3d::Shader shaderTerrain("res/shaders/terrain_vertex.glsl", "res/shaders/terrain_fragment.glsl");

	////////////////////////////////////////////////
	//	Create the renderer and camera objects
	////////////////////////////////////////////////

	as3d::Renderer renderer;
	as3d::Camera camera(glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 500.0f));
	renderer.SetClearColor(0.2f, 0.2f, 0.2f);

	while (!window.ShouldClose())
	{
		renderer.Clear();

		// Update the camera position
		camera.OnUpdate(window.GetDeltaTime());

		// Render the skybox
		shaderSkybox.Bind();
		shaderSkybox.SetMatrix4("viewMatrix", glm::mat3(camera.GetViewMatrix()));
		shaderSkybox.SetMatrix4("projectionMatrix", camera.GetProjectionMatrix());
		skybox.Draw(shaderSkybox);

		// Render the nanosuit model
		shaderNanoSuit.Bind();
		shaderNanoSuit.SetMatrix4("viewMatrix", camera.GetViewMatrix());
		shaderNanoSuit.SetMatrix4("projectionMatrix", camera.GetProjectionMatrix());
		shaderNanoSuit.SetVector3("lightPosition", light.GetPosition());
		shaderNanoSuit.SetVector3("cameraPosition", camera.GetPosition());
		nanoSuit.Draw(shaderNanoSuit);

		// Render the terrain
		shaderTerrain.Bind();
		shaderTerrain.SetMatrix4("viewProjectionMatrix", camera.GetViewProjectionMatrix());
		shaderTerrain.SetVector3("lightPosition", light.GetPosition());
		terrain.Draw(shaderTerrain);

		// Render the light source
		shaderLight.Bind();
		shaderLight.SetMatrix4("viewProjectionMatrix", camera.GetViewProjectionMatrix());
		light.Draw(shaderLight);

		// Render the GUI
		imgui.BeginFrame();
		camera.DrawControlWindow("camera");
		nanoSuit.DrawControlWindow("models");
		light.DrawControlWindow("light");
		renderer.DrawControlWindow("renderer");
		//imgui.DrawDemoWindow();

		imgui.EndFrame();

		window.Update();
	}

	return 0;
}