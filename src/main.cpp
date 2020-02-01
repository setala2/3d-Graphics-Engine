#include "GL/glew.h"

#include "GlfwManager.h"
#include "ImguiManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Renderer.h"
#include "Model.h"
#include "Camera.h"
#include "LightSource.h"
#include "Texture.h"
#include "Drawable.h"

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

	Assimp::Importer imp;
	auto model = imp.ReadFile("models/teapot2.obj",
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices
	);


	while (!glfwWindowShouldClose(window))
	{
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}