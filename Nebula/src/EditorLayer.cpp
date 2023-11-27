#include "EditorLayer.h"
#include "imgui.h"
#include <Void/ECS/Components/CameraComponent.h>
#include "Void/ECS/Components/CameraControllerComponent.h"
#include <Void/ECS/Systems/Camera/CameraSystem.h>
#include <Void/ECS/Systems/Camera/CameraControllerSystem.h>
#include <Void/ECS/Systems/AudioListener/AudioListenerSystem.h>
#include <Void/ECS/Components/AudioListenerComponent.h>
#include <Void/ECS/Components/VelocityComponent.h>
#include <Void/ECS/Components/FootstepComponent.h>
#include <Void/ECS/Systems/Footsteps/FootstepSystem.h>
#include <Void/Audio/AudioManager/AudioManager.h>



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
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Cabin.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Barn.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Barrel_Alcohol.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Barrel_Dirt.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Barrel_Sand.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Barricade_Wood.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Cactus_1.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Cactus_2.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Cactus_3.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Fort_Tower.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Fort_Walkway.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Grass_Shrub.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Mexican_Building_2.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Mexican_Building_3.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Mexican_Building_4.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Outhouse.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Rocks.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Teepee_1.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Teepee_2.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Tower.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Plane.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Female_Weapon_1.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Female_Weapon_2.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Male_Cover.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Male_Cower.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Male_Weapon_1.obj");
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Male_Weapon_2.obj");

        // Texture lib
        Void::TextureLibrary::GetInstance()->Load("Temp/Models/Western_Texture.png");
        Void::TextureLibrary::GetInstance()->Load("Temp/Models/PolygonPrototype_Texture_04.png");
        Void::TextureLibrary::GetInstance()->Load("Temp/Models/PolygonPrototype_Texture_02.png");

        // Sound lib
        Void::Audio::AudioManager::GetInstance()->Load3DAudio("Temp/Sound/footstep-gravel.wav");

        m_SceneManager = new Void::SceneManager();
        m_SceneManager->LoadScene("Scene7.json");

        //entt::entity en = m_SceneManager->GetCurrentScene()->CreateEntity();
        //m_SceneManager->GetCurrentScene()->AddComponent<Void::TransformComponent>(en);
        //Void::PhysicsComponent& pc = m_SceneManager->GetCurrentScene()->AddComponent<Void::PhysicsComponent>(en);
        //pc.Collider = new Void::SphereCollider();
        //Void::TagComponent& tag = m_SceneManager->GetCurrentScene()->AddComponent<Void::TagComponent>(en);
        //tag.Tag = "Player";
        //m_SceneManager->SaveScene("Scene7.json");

        std::shared_ptr<Void::Rendering::RenderingSystem> renderingSystem = std::make_shared<Void::Rendering::RenderingSystem>();
        m_SceneManager->GetCurrentScene()->SetRenderingSystem(renderingSystem);

        std::shared_ptr<Void::PhysicsSystem> physicsSystem = std::make_shared<Void::PhysicsSystem>();
        m_SceneManager->GetCurrentScene()->SetPhysicsSystem(physicsSystem);
        physicsSystem->AddSolver(std::make_shared<Void::PositionSolver>());
        physicsSystem->AddSolver(std::make_shared<Void::ImpulseSolver>());

        std::shared_ptr<Void::CameraSystem> cameraSystem = std::make_shared<Void::CameraSystem>();
        m_SceneManager->GetCurrentScene()->AddSystem(cameraSystem);

        std::shared_ptr<Void::CameraControllerSystem> cameraControllerSystem = std::make_shared<Void::CameraControllerSystem>();
        m_SceneManager->GetCurrentScene()->AddSystem(cameraControllerSystem);

        std::shared_ptr<Void::AudioListenerSystem> audioListenerSystem = std::make_shared<Void::AudioListenerSystem>();
        m_SceneManager->GetCurrentScene()->AddSystem(audioListenerSystem);

        std::shared_ptr<Void::FootstepSystem> footstepSystem = std::make_shared<Void::FootstepSystem>();
        m_SceneManager->GetCurrentScene()->AddSystem(footstepSystem);

        Void::Entity* entity = m_SceneManager->GetCurrentScene()->CreateEntity();
        entity->AddComponent<Void::CameraControllerComponent>();
        entity->AddComponent<Void::AudioListenerComponent>();
        entity->AddComponent<Void::TransformComponent>();
        Void::TransformComponent& t = entity->GetComponent<Void::TransformComponent>();
        t.Position = glm::vec3(0, .5, 0);
        entity->AddComponent<Void::VelocityComponent>();
        entity->AddComponent<Void::FootStepComponent>();
        entity->AddComponent<Void::CameraComponent>();
	}

    void EditorLayer::OnUpdate()
    {
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