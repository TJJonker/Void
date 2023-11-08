#include "EditorLayer.h"
#include "imgui.h"

namespace Nebula::Editor {

	void EditorLayer::OnAdded()
	{
        Void::Rendering::FrameBufferConfig config;
        config.width = 1280;
        config.height = 720;
        m_FrameBuffer = Void::Rendering::FrameBuffer::Create(config);

        m_Scene = new Void::Scene();
        m_CameraController = new Void::CameraController();

        std::shared_ptr<Void::Rendering::RenderingSystem> renderingSystem = std::make_shared<Void::Rendering::RenderingSystem>();
        m_Scene->SetRenderingSystem(renderingSystem);

        ////////////////////
        //Insert code here
        {
            entt::entity entity1 = m_Scene->CreateEntity();

            std::shared_ptr<Void::Rendering::Shader> shader;
            shader.reset(Void::Rendering::Shader::Create("Temp/Shaders/VertexShader.glsl", "Temp/Shaders/FragmentShader.glsl"));

            std::shared_ptr<Void::Rendering::Texture> texture;
            texture.reset(Void::Rendering::Texture::Create("Temp/Models/SimpleCity_Texture.png"));

            //Void::Rendering::Model* model1 = Void::ModelLoader::LoadModel("Temp/Models/Building.obj");
            //model1->Submeshes[0]->Shader = shader;
            //model1->Submeshes[0]->Textures.push_back(texture);

            Void::RenderingComponent& rc = m_Scene->AddComponent<Void::RenderingComponent>(entity1);
            Void::Rendering::Submesh submesh;
            submesh.Model = "Horse";
            submesh.Shader = "HorseShador";
            submesh.Textures.push_back("HorseDiffuse");
            submesh.Textures.push_back("HorseSpecular");
            submesh.Textures.push_back("HorseBump");
            rc.Submeshes.push_back(submesh);

            Void::TransformComponent& tc = m_Scene->AddComponent<Void::TransformComponent>(entity1);
            tc.Position = glm::vec3(0, 0, -15);
            tc.Scale = glm::vec3(0.4, 0.4, 0.4);
        }
        {
            entt::entity entity1 = m_Scene->CreateEntity();

            Void::RenderingComponent& rc = m_Scene->AddComponent<Void::RenderingComponent>(entity1);
            {
                Void::Rendering::Submesh submesh;
                submesh.Model = "Croissant";
                submesh.Shader = "CroissantShador";
                submesh.Textures.push_back("CroissantDiffuse");
                submesh.Textures.push_back("CroissantSpecular");
                submesh.Textures.push_back("CroissantBump");
                rc.Submeshes.push_back(submesh);
            }

            {
                Void::Rendering::Submesh submesh;
                submesh.Model = "Baguette";
                submesh.Shader = "BaguetteShador";
                submesh.Textures.push_back("BaguetteDiffuse");
                submesh.Textures.push_back("BaguetteSpecular");
                submesh.Textures.push_back("BaguetteBump");
                rc.Submeshes.push_back(submesh);
            }

            Void::TransformComponent& tc = m_Scene->AddComponent<Void::TransformComponent>(entity1);
            tc.Position = glm::vec3(102, 35, 2);
            tc.Scale = glm::vec3(0.6, 0.6, 1);
        }


        Void::SceneManager sceneManager;
        sceneManager.SetScene(m_Scene);
        sceneManager.SaveScene("Scene1.json");

	}

    void EditorLayer::OnUpdate()
    {
        m_CameraController->Update(); 
        Void::Rendering::RenderingCommands::BeginDraw(m_CameraController->GetCamera()); 

        m_FrameBuffer->Bind();
        Void::Rendering::RenderingCommands::SetClearColor({ .1, .2, .1, 1 });
        Void::Rendering::RenderingCommands::Clear();
        m_Scene->UpdateRenderingSystem();
        m_FrameBuffer->UnBind();
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