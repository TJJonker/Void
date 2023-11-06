#include "EditorLayer.h"
#include "imgui.h"

namespace Nebula::Editor {

	void EditorLayer::OnAdded()
	{
        Void::Rendering::FrameBufferConfig config;
        config.width = 1280;
        config.height = 720;
        m_FrameBuffer = Void::Rendering::FrameBuffer::Create(config);
	}

	void EditorLayer::OnGuiRender()
	{
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        bool open = true;
        ImGui::Begin("DockSpace Demo", &open, window_flags);

        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        //if (ImGui::BeginMenuBar())
        //{
        //    if (ImGui::BeginMenu("Options"))
        //    {
        //        ImGui::MenuItem("Test", NULL);
        //        ImGui::EndMenu();
        //    }
        //    ImGui::EndMenuBar();
        //}


        ImGui::Begin("Scene");
        ImGui::Image((ImTextureID)m_FrameBuffer->GetRenderingID(), ImVec2{ 1280, 720 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();


        ImGui::End();
	}
}