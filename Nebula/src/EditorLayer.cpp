#include "EditorLayer.h"


namespace Nebula::Editor {

	void EditorLayer::OnAdded()
	{
        Void::SceneManager::GetInstance().LoadScene("Scene7.json");

        m_Dockspace = new Window::GeneralDockspace();
        m_Dockspace->Initialize();

        // Temp
        // Shader lib
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShader.glsl", "DefaultShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Core/Shaders/DefaultSkybox/VertexShader.glsl", "Assets/Core/Shaders/DefaultSkybox/FragmentShader.glsl", "DefaultSkyboxShader");

        // Texture lib
        Void::TextureLibrary::GetInstance().LoadTexture("Assets/Textures/PolygonHeist_Texture_03_C.png");
        Void::TextureLibrary::GetInstance().LoadTexture("Assets/Textures/PolygonCity_Texture_04_A.png");

        // Cubemaps
        Void::TextureLibrary::GetInstance().LoadCubemap("Default",
            {
                "Assets/Skybox/DefaultSkybox/right.jpg",
                "Assets/Skybox/DefaultSkybox/left.jpg",
                "Assets/Skybox/DefaultSkybox/top.jpg",
                "Assets/Skybox/DefaultSkybox/bottom.jpg",
                "Assets/Skybox/DefaultSkybox/front.jpg",
                "Assets/Skybox/DefaultSkybox/back.jpg",
            });

        // Mesh lib
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_02.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_03.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Arrow_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Arrow_02.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Bare_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Crossing_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Lines_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Lines_02.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Median_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Median_02.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_ParkingLines_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_Patch_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_YellowLines_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Road_YellowLines_02.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Core/Models/Cube.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Door_Glass_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Prop_WaterCooler_Tank_01.obj");

#include "Void/ECS/Core/Scene/SceneManager.h"

        Void::Entity* en = Void::SceneManager::GetInstance().GetCurrentScene()->CreateEntity();
        en->AddComponent<Void::BoxCollider3DComponent>();
        Void::SceneManager::GetInstance().SaveScene("Scene8.json");


        std::shared_ptr<Void::Rendering::RenderingSystem> renderingSystem = std::make_shared<Void::Rendering::RenderingSystem>();
        Void::SceneManager::GetInstance().GetCurrentScene()->SetRenderingSystem(renderingSystem);

        
        //std::shared_ptr<Void::PhysicsSystem> physicsSystem = std::make_shared<Void::PhysicsSystem>();
        //m_SceneManager->GetCurrentScene()->SetPhysicsSystem(physicsSystem);
        //physicsSystem->AddSolver(std::make_shared<Void::PositionSolver>());
        //physicsSystem->AddSolver(std::make_shared<Void::ImpulseSolver>());
	}

    void EditorLayer::OnEvent(Void::Event& event)
    {
        m_Dockspace->OnEvent(event);
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