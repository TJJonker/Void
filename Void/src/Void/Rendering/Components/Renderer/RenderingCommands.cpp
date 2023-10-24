#include "pch.h"
#include "RenderingCommands.h"

namespace Void {
	void RenderingCommands::SetClearColor(const glm::vec4& color)
	{
		m_Renderer->SetClearColor(color);
	}

	void RenderingCommands::Clear()
	{
		m_Renderer->Clear();
	}

	void RenderingCommands::Draw(const std::shared_ptr<VertexArray> vertexArray, const std::shared_ptr<Shader> shader, glm::mat4 viewMatrix)
	{
		shader->Bind();
		shader->SetMatrix4("view", viewMatrix);

		vertexArray->Bind();
		m_Renderer->Draw(vertexArray);
	}
}