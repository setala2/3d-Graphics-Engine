#include "ImguiManager.h"

unsigned int ImguiManager::refCount = 0;

ImguiManager::ImguiManager(GLFWwindow* window)
{
	if (refCount++ == 0)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}
}

ImguiManager::~ImguiManager()
{
	if (--refCount == 0)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}

void ImguiManager::BeginFrame()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImguiManager::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::DrawDemoWindow()
{
	ImGui::ShowDemoWindow((bool*)1);
}
