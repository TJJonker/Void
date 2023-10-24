#include "pch.h"
#include "Application.h"
#include "Window.h"
#include <Void/Rendering/Components/VertexBuffer/VertexBuffer.h>
#include "Void/Rendering/Components/VertexBufferLayout/VertexBufferLayout.h"
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"
#include "Input.h"
#include "Void/Utils/TimeSteps/Time.h"

namespace Void {

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// Create a new window.
		m_Window = Window::Create();
		// Forward the window events to the OnEvent method.
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

		//m_VertexArray = std::make_shared<VertexArray>(VertexArray::Create());
		m_VertexArray.reset(VertexArray::Create());

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		VertexBufferLayout bufferLayout;
		bufferLayout.Push<float>(3); // Position
		bufferLayout.Push<float>(4); // Color
		vertexBuffer->SetVertexBufferLayout(bufferLayout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Shader::Create("Temp/Shaders/VertexShader.glsl", "Temp/Shaders/FragmentShader.glsl"));
	}
	
	Application::~Application()	{ }

	void Application::OnEvent(Event& e)
	{
		EventDelegator delegator(e);
		delegator.Delegate<WindowCloseEvent>(BIND_EVENT_FUNCTION(CloseApplication));
	}

	void Application::Run() {
		while (m_IsRunning) {
			
			Time::Update();

			RenderingCommands::SetClearColor({ .1, .2, .1, 1 });
			RenderingCommands::Clear();

			m_Shader->Bind();
			m_VertexArray->Bind();
			RenderingCommands::Draw(m_VertexArray);

			m_Window->OnUpdate();
		}
	}

	bool Application::CloseApplication(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}

