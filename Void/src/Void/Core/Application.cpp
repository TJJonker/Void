#include "pch.h"
#include "Application.h"
#include "Window.h"
#include <Void/Rendering/Components/VertexBuffer/VertexBuffer.h>
#include "Void/Rendering/Components/VertexBufferLayout/VertexBufferLayout.h"
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"
#include "Input.h"
#include "Void/Utils/TimeSteps/Time.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Void/Rendering/Components/Model/Model.h>
#include <Void/Utils/ExternalFiles/ModelLoader.h>
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/RenderingComponent.h>
#include <Void/ECS/Systems/RenderingSystem.h>

namespace Void {

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::application = nullptr;

	Application::Application()
	{
		VOID_CORE_ASSERT(!application, "Application already exists.");
		application = this;

		//// Create a new window.
		m_Window = Window::Create();

		// Forward the window events to the OnEvent method.
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

		m_CameraController = new CameraController();

		m_Scene = new Scene();

		std::shared_ptr<RenderingSystem> renderingSystem = std::make_shared<RenderingSystem>(); 
		m_Scene->SetRenderingSystem(renderingSystem); 


		////////////////////
		/// Insert code here


		entt::entity entity1 = m_Scene->CreateEntity();

		std::shared_ptr<Shader> shader;
		shader.reset(Shader::Create("Temp/Shaders/VertexShader.glsl", "Temp/Shaders/FragmentShader.glsl"));

		std::shared_ptr<Texture> texture;
		texture.reset(Texture::Create("Temp/Models/SimpleCity_Texture.png"));


		Model* model1 = ModelLoader::LoadModel("Temp/Models/Building.obj");
		model1->Submeshes[0]->Shader = shader;
		model1->Submeshes[0]->Textures.push_back(texture);

		RenderingComponent& rc = m_Scene->AddComponent<RenderingComponent>(entity1);
		rc.Submeshes = model1->Submeshes;

		TransformComponent& tc = m_Scene->AddComponent<TransformComponent>(entity1);
		tc.Position = glm::vec3(0, 0, -15);
		tc.Scale = glm::vec3(0.4, 0.4, 0.4);
	}
	
	Application::~Application()	{ }

	void Application::OnEvent(Event& e)
	{
		EventDelegator delegator(e);
		delegator.Delegate<WindowCloseEvent>(BIND_EVENT_FUNCTION(CloseApplication));

		for (Layer* layer : m_LayerStack) {
			layer->OnEvent(e);
			if (e.Consumed)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::Run() {

		while (m_IsRunning) {			
			Time::Update();

			m_CameraController->Update();

			RenderingCommands::SetClearColor({ .1, .2, .1, 1 });
			RenderingCommands::Clear();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			RenderingCommands::BeginDraw(m_CameraController->GetCamera());
			m_Scene->UpdateRenderingSystem();

			m_Window->OnUpdate();
		}
	}

	bool Application::CloseApplication(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	Application& Application::Get()
	{
		return *application;
	}

	Window* Application::GetWindow()
	{
		return m_Window;
	}
}

