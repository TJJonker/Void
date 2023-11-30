#include "GeneralDockspace.h"
#include <imgui.h>
#include "Windows/Menus/Menu/FileMenu.h"

namespace Nebula::Window {
	void GeneralDockspace::Initialize()
	{
		m_Window_flags |= ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		m_Window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
		m_Window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoMove;
		m_Viewport = ImGui::GetMainViewport();

		m_MenuManagers.push_back(new FileMenu("File"));
		m_MenuManagers.push_back(new FileMenu("Edit"));
		m_MenuManagers.push_back(new FileMenu("View"));
	}

	void GeneralDockspace::Render()
	{		
		ImGui::SetNextWindowPos(m_Viewport->GetWorkPos());
		ImGui::SetNextWindowSize(m_Viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(m_Viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Yooo", &IsOpen, m_Window_flags);
		ImGui::PopStyleVar(3);

		RenderContent();
		
		ImGui::End();
	}

	void GeneralDockspace::RenderContent()
	{
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
		}

		
		if (ImGui::BeginMenuBar()) {
			for (Menu* manager : m_MenuManagers)
				manager->RenderMenu();
			ImGui::EndMenuBar();
		}
	}
}
