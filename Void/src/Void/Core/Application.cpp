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

namespace Void {

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// Create a new window.
		m_Window = Window::Create();
		// Forward the window events to the OnEvent method.
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

		m_CameraController = new CameraController();

		Model* model1 = ModelLoader::LoadModel("Temp/Models/Building.obj");

		//m_VertexArray.reset(VertexArray::Create());
		m_VertexArray = model1->Submeshes[0]->VertexArray;

		//float vertices[24] = {
		//	 -0.5f, -0.5f, -0.5f,
		//	  0.5f, -0.5f, -0.5f,
		//	  0.5f,  0.5f, -0.5f,
		//	 -0.5f,  0.5f, -0.5f,
		//	 -0.5f, -0.5f,  0.5f,
		//	  0.5f, -0.5f,  0.5f,
		//	  0.5f,  0.5f,  0.5f,
		//	 -0.5f,  0.5f,  0.5f
		//};

		//std::shared_ptr<VertexBuffer> vertexBuffer;
		//vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		//
		//VertexBufferLayout bufferLayout;
		//bufferLayout.Push<float>(3); // Position
		//vertexBuffer->SetVertexBufferLayout(bufferLayout);
		//m_VertexArray->AddVertexBuffer(vertexBuffer);
		//
		//uint32_t indices[36] = { 
		//	0, 1, 2, 0, 2, 3,
		//	4, 5, 6, 4, 6, 7,
		//	3, 2, 6, 2, 6, 7,
		//	0, 1, 6, 0, 5, 4,
		//	0, 3, 7, 0, 7, 4,
		//	1, 2, 6, 1, 6, 5
		//};
		//std::shared_ptr<IndexBuffer> indexBuffer;
		//indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		//m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Shader::Create("Temp/Shaders/VertexShader.glsl", "Temp/Shaders/FragmentShader.glsl"));
		m_Shader->Bind();

		glm::mat4 projection = glm::perspective(glm::radians(m_CameraController->GetCamera()->GetFOV()), 1280.0f / 720.0f, 0.1f, 100.0f); 
		glm::mat4 viewMatrix = m_CameraController->GetCamera()->GetView(); 
		glm::mat4 model = glm::mat4(1.0f); 
		 
		model = glm::translate(model, glm::vec3(0.f, 0.f, -15.f)); 
		model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
		model = glm::scale(model, glm::vec3(.4f, .4f, .4f));
		 
		m_Shader->SetMatrix4("projection", projection); 
		m_Shader->SetMatrix4("view", viewMatrix); 
		m_Shader->SetMatrix4("model", model); 
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
			m_CameraController->Update();

			RenderingCommands::SetClearColor({ .1, .2, .1, 1 });
			RenderingCommands::Clear();

			RenderingCommands::Draw(m_VertexArray, m_Shader, m_CameraController->GetCamera()->GetView());

			m_Window->OnUpdate();
		}
	}

	bool Application::CloseApplication(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}

