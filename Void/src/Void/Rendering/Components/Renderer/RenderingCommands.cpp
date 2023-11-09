#include "pch.h"
#include "RenderingCommands.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Void::Rendering {

	RenderingCommands::RenderData* RenderingCommands::m_RenderData = new RenderingCommands::RenderData();

	void RenderingCommands::SetClearColor(const glm::vec4& color)
	{
		m_Renderer->SetClearColor(color);
	}

	void RenderingCommands::Clear()
	{
		m_Renderer->Clear();
	}

	void RenderingCommands::BeginDraw(Camera* camera)
	{
		m_RenderData->viewMatrix = camera->GetView();
		m_RenderData->projectionMatrix = glm::perspective(glm::radians(camera->GetFOV()), 1280.0f / 720.0f, 0.1f, 100.0f);
		m_RenderData->viewPosition = camera->GetPosition();
	}

	void RenderingCommands::Draw(VertexArray* vertexArray, Shader* shader, glm::mat4 modelMatrix)
	{
		shader->Bind();
		shader->SetMatrix4("viewMatrix", m_RenderData->viewMatrix);
		shader->SetMatrix4("projectionMatrix", m_RenderData->projectionMatrix);
		shader->SetMatrix4("modelMatrix", modelMatrix);
		shader->SetVec3("viewPosition", m_RenderData->viewPosition);

		/// TEMP
		glm::vec3 lightDirection = { 1.f, 0.f, 0.2f };
		glm::vec3 ambientColor = { .3f, .3f, .3f };
		glm::vec3 diffuseColor = { .7f, .7f, .7f };
		glm::vec3 specularColor = { 1.f, 1.f, 1.f };

		shader->SetVec3("directionalLight.direction", lightDirection);
		shader->SetVec3("directionalLight.ambient", ambientColor);
		shader->SetVec3("directionalLight.diffuse", diffuseColor);
		shader->SetVec3("directionalLight.specular", specularColor);
		///

		vertexArray->Bind();
		m_Renderer->Draw(vertexArray);
	}
}