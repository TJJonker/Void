#include "EditorLayer.h"
#include "imgui.h"



namespace Nebula::Editor {

	void EditorLayer::OnAdded()
	{
        Void::Rendering::FrameBufferConfig config;
        config.width = 1280;
        config.height = 720;
        m_FrameBuffer = Void::Rendering::FrameBuffer::Create(config);


        // Temp
        // Shader lib
        Void::ShaderLibrary::GetInstance()->Load("Temp/Shaders/VertexShader.glsl", "Temp/Shaders/FragmentShader.glsl", "DefaultShader");

        // Mesh lib
 

        // Texture lib

        m_SceneManager = new Void::SceneManager();
        m_SceneManager->LoadScene("Scene7.json");

        //entt::entity en = m_SceneManager->GetCurrentScene()->CreateEntity();
        //m_SceneManager->GetCurrentScene()->AddComponent<Void::TransformComponent>(en);
        //Void::PhysicsComponent& pc = m_SceneManager->GetCurrentScene()->AddComponent<Void::PhysicsComponent>(en);
        //pc.Collider = new Void::SphereCollider();
        //Void::TagComponent& tag = m_SceneManager->GetCurrentScene()->AddComponent<Void::TagComponent>(en);
        //tag.Tag = "Player";
        //m_SceneManager->SaveScene("Scene7.json");

        m_CameraController = new Void::CameraController();

        std::shared_ptr<Void::Rendering::RenderingSystem> renderingSystem = std::make_shared<Void::Rendering::RenderingSystem>();
        m_SceneManager->GetCurrentScene()->SetRenderingSystem(renderingSystem);

        std::shared_ptr<Void::PhysicsSystem> physicsSystem = std::make_shared<Void::PhysicsSystem>();
        m_SceneManager->GetCurrentScene()->SetPhysicsSystem(physicsSystem);
        physicsSystem->AddSolver(std::make_shared<Void::PositionSolver>());
        physicsSystem->AddSolver(std::make_shared<Void::ImpulseSolver>());

	}

    void EditorLayer::OnUpdate()
    {
        m_CameraController->Update(); 
        Void::Rendering::RenderingCommands::BeginDraw(m_CameraController->GetCamera()); 

        m_SceneManager->GetCurrentScene()->UpdateSystems();
        m_SceneManager->GetCurrentScene()->UpdatePhysicsSystem();

        //m_FrameBuffer->Bind();
        Void::Rendering::RenderingCommands::SetClearColor({ .1, .2, .1, 1 });
        Void::Rendering::RenderingCommands::Clear();
        m_SceneManager->GetCurrentScene()->UpdateRenderingSystem();
        //m_FrameBuffer->UnBind();
    } 

	void EditorLayer::OnGuiRender()
	{
        //static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        //// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        //// because it would be confusing to have two docking targets within each others.
        //ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        //
        //ImGuiViewport* viewport = ImGui::GetMainViewport();
        //ImGui::SetNextWindowPos(viewport->GetWorkPos());
        //ImGui::SetNextWindowSize(viewport->GetWorkSize());
        //ImGui::SetNextWindowViewport(viewport->ID);
        //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        //window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        //window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        //
        //bool open = true;
        //ImGui::Begin("DockSpace Demo", &open, window_flags);

        //ImGui::PopStyleVar();
        //ImGui::PopStyleVar(2);

        //// DockSpace
        //ImGuiIO& io = ImGui::GetIO();
        //if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        //{
        //    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        //    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        //}

        //if (ImGui::BeginMenuBar())
        //{
        //    if (ImGui::BeginMenu("Options"))
        //    {
        //        ImGui::MenuItem("Test", NULL);
        //        ImGui::EndMenu();
        //    }
        //    ImGui::EndMenuBar();
        //}


        //ImGui::Begin("Scene");
        //ImGui::Image((ImTextureID)m_FrameBuffer->GetRenderingID(), ImVec2{ 1280, 720 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        //ImGui::End();


        //ImGui::End();
	}
}