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

		/// TEMP
		glm::vec3 lightDirection = { 1.f, 0.f, 0.2f };
		glm::vec3 ambientColor = { .1f, .1f, .1f };
		glm::vec3 diffuseColor = { .3f, .3f, .3f };
		glm::vec3 specularColor = { 1.f, 1.f, 1.f };
		///


		// Create a new window.
		m_Window = Window::Create();
		// Forward the window events to the OnEvent method.
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

		m_CameraController = new CameraController();

		Model* model1 = ModelLoader::LoadModel("Temp/Models/Building.obj");
		m_VertexArray = model1->Submeshes[0]->VertexArray;

		m_Shader.reset(Shader::Create("Temp/Shaders/VertexShader.glsl", "Temp/Shaders/FragmentShader.glsl"));
		m_Shader->Bind();
		m_Shader->SetVec3("directionalLight.direction", lightDirection);
		m_Shader->SetVec3("directionalLight.ambient", ambientColor);
		m_Shader->SetVec3("directionalLight.diffuse", diffuseColor);
		m_Shader->SetVec3("directionalLight.specular", specularColor);
	}
	
	Application::~Application()	{ }

	void Application::OnEvent(Event& e)
	{
		EventDelegator delegator(e);
		delegator.Delegate<WindowCloseEvent>(BIND_EVENT_FUNCTION(CloseApplication));
	}

	void Application::Run() {

		/// TEMP
		glm::mat4 model = glm::mat4(1.0f); 

		model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f)); 
		model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f)); 
		model = glm::scale(model, glm::vec3(.4f, .4f, .4f)); 
		///

		while (m_IsRunning) {
			
			Time::Update();
			m_CameraController->Update();

			RenderingCommands::SetClearColor({ .1, .2, .1, 1 });
			RenderingCommands::Clear();

			/// TEMP
			m_Shader->Bind();
			m_Shader->SetVec3("viewPosition", m_CameraController->GetCamera()->GetPosition());
			RenderingCommands::BeginDraw(m_CameraController->GetCamera()->GetView(), glm::perspective(glm::radians(m_CameraController->GetCamera()->GetFOV()), 1280.0f / 720.0f, 0.1f, 100.0f));
			///
			RenderingCommands::Draw(m_VertexArray, m_Shader, model);

			m_Window->OnUpdate();
		}
	}

	bool Application::CloseApplication(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}

