#include "EditorLayer.h"
#include <Void/ECS/Systems/Light/PointLightSystem.h>


namespace Nebula::Editor {

	void EditorLayer::OnAdded()
	{
        Void::SceneManager::GetInstance().LoadScene("Scene7.json");

        m_Dockspace = new Window::GeneralDockspace();
        m_Dockspace->Initialize();

        // Temp
        // Shader lib
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShaderAnimating.glsl", "AnimatingShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShaderFire.glsl", "Assets/Shaders/FragmentShaderBlending.glsl", "BlendingShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShader.glsl", "DefaultShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShaderSpecular.glsl", "SpecularShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShaderMoving.glsl", "MovingShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShaderCubemapReflection.glsl", "CubemapRefractionShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Shaders/VertexShaderTransparency.glsl", "Assets/Shaders/FragmentShaderTransparency.glsl", "BeamShader");
        Void::ShaderLibrary::GetInstance()->Load("Assets/Core/Shaders/DefaultSkybox/VertexShader.glsl", "Assets/Core/Shaders/DefaultSkybox/FragmentShader.glsl", "DefaultSkyboxShader");

        // Texture lib
        Void::TextureLibrary::GetInstance().LoadTexture("Assets/Textures/Dungeons_2_Texture_01_A.png");
        Void::TextureLibrary::GetInstance().LoadTexture("Assets/Textures/PolygonCity_Texture_01_A.png");
        Void::TextureLibrary::GetInstance().LoadTexture("Assets/Textures/lroc_color_poles_4k.jpg");
        Void::TextureLibrary::GetInstance().LoadTexture("Assets/Textures/Fire.png");
        Void::TextureLibrary::GetInstance().LoadTexture("Assets/Textures/Beholder_Base_color.png");


        // Cubemaps
        Void::TextureLibrary::GetInstance().LoadCubemap("Default",
            {
                "Assets/Skybox/Space/right.jpg",
                "Assets/Skybox/Space/left.jpg",
                "Assets/Skybox/Space/top.jpg",
                "Assets/Skybox/Space/bottom.jpg",
                "Assets/Skybox/Space/front.jpg",
                "Assets/Skybox/Space/back.jpg",
            });

        // Mesh lib
        Void::MeshLibrary::GetInstance()->Load("Assets/Core/Models/Cube.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Core/Models/Plane.obj");
        

        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Dwarf_Wall_01.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/Moon.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Dwarf_Wall_Archway_01.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Sidewalk_01.obj");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Prop_Dwarf_Torch_06.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Prop_Dwarf_Torch_01.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Crystals_Cluster_Large_04.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/Beholder.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/vision_cone.ply");
        Void::MeshLibrary::GetInstance()->Load("Assets/Models/SM_Env_Grass_01.obj");


        //Void::Entity* entity = Void::SceneManager::GetInstance().GetCurrentScene()->CreateEntity();
        //entity->AddComponent<Void::PointLightComponent>();
        //Void::SceneManager::GetInstance().SaveScene("Scene8.json");

        {
            std::shared_ptr<Void::Rendering::RenderingSystem> renderingSystem = std::make_shared<Void::Rendering::RenderingSystem>();
            Void::SceneManager::GetInstance().GetCurrentScene()->SetRenderingSystem(renderingSystem);
        }

        {
            std::shared_ptr<Void::PointLightSystem> pointLightSystem = std::make_shared<Void::PointLightSystem>();
            Void::SceneManager::GetInstance().GetCurrentScene()->AddSystem(pointLightSystem);
        }

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