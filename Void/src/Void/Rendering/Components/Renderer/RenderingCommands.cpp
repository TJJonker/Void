#include "pch.h"
#include "RenderingCommands.h"

namespace Void {

	RenderingCommands::RenderData* RenderingCommands::m_RenderData = new RenderingCommands::RenderData();

	void RenderingCommands::SetClearColor(const glm::vec4& color)
	{
		m_Renderer->SetClearColor(color);
	}

	void RenderingCommands::Clear()
	{
		m_Renderer->Clear();
	}

	void RenderingCommands::BeginDraw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
	{
		m_RenderData->viewMatrix = viewMatrix;
		m_RenderData->projectionMatrix = projectionMatrix;
	}

	void RenderingCommands::Draw(const std::shared_ptr<VertexArray> vertexArray, const std::shared_ptr<Shader> shader, glm::mat4 modelMatrix)
	{
		shader->Bind();
		shader->SetMatrix4("viewMatrix", m_RenderData->viewMatrix);
		shader->SetMatrix4("projectionMatrix", m_RenderData->projectionMatrix);
		shader->SetMatrix4("modelMatrix", modelMatrix);

		vertexArray->Bind();
		m_Renderer->Draw(vertexArray);
	}
}