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

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
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
		layer->OnAdded();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAdded();
	}

	void Application::Run() {

		while (m_IsRunning) {			
			Time::Update();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->StartRendering();
			for (Layer* layer : m_LayerStack)
				layer->OnGuiRender();
			m_ImGuiLayer->EndRendering();

			m_Window->OnUpdate();
		}
	}

	bool Application::CloseApplication(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}

