#include "EditorLayer.h"


namespace Nebula::Editor {

	void EditorLayer::OnAdded()
	{
        Void::SceneManager::GetInstance().LoadScene("Scene7.json");

        m_Dockspace = new Window::GeneralDockspace();
        m_Dockspace->Initialize();


        // Temp
        // Shader lib
        Void::ShaderLibrary::GetInstance()->Load("Temp/Shaders/VertexShader.glsl", "Temp/Shaders/FragmentShader.glsl", "DefaultShader");

        // Texture lib
        Void::TextureLibrary::GetInstance()->Load("Temp/Textures/PolygonPrototype_Texture_06.png");

        // Mesh lib
        Void::MeshLibrary::GetInstance()->Load("Temp/Models/Barn.obj");



        //entt::entity en = m_SceneManager->GetCurrentScene()->CreateEntity();
        //m_SceneManager->GetCurrentScene()->AddComponent<Void::TransformComponent>(en);
        //Void::PhysicsComponent& pc = m_SceneManager->GetCurrentScene()->AddComponent<Void::PhysicsComponent>(en);
        //pc.Collider = new Void::SphereCollider();
        //Void::TagComponent& tag = m_SceneManager->GetCurrentScene()->AddComponent<Void::TagComponent>(en);
        //tag.Tag = "Player";
        //m_SceneManager->SaveScene("Scene7.json");


        std::shared_ptr<Void::Rendering::RenderingSystem> renderingSystem = std::make_shared<Void::Rendering::RenderingSystem>();
        Void::SceneManager::GetInstance().GetCurrentScene()->SetRenderingSystem(renderingSystem);

        //std::shared_ptr<Void::PhysicsSystem> physicsSystem = std::make_shared<Void::PhysicsSystem>();
        //m_SceneManager->GetCurrentScene()->SetPhysicsSystem(physicsSystem);
        //physicsSystem->AddSolver(std::make_shared<Void::PositionSolver>());
        //physicsSystem->AddSolver(std::make_shared<Void::ImpulseSolver>());
	}

    void EditorLayer::OnUpdate()
    {
        //Void::SceneManager::GetInstance().GetCurrentScene()->UpdateSystems();
        //Void::SceneManager::GetInstance().GetCurrentScene()->UpdatePhysicsSystem();
    } 

	void EditorLayer::OnGuiRender()
	{
        m_Dockspace->Render();
	}
}