#include "SceneViewWindow.h"

namespace Nebula::Window {
	
	void SceneViewWindow::OnAdded()
	{
		Void::Rendering::FrameBufferConfig config{};
		m_FrameBuffer = Void::Rendering::FrameBuffer::Create(config);
	}

	void SceneViewWindow::OnGuiRender()
	{
		m_FrameBuffer->Bind();
		Void::Rendering::RenderingCommands::SetClearColor({ .1, .2, .1, 1 });
		Void::Rendering::RenderingCommands::Clear();
		Void::SceneManager::GetInstance().GetCurrentScene()->UpdateRenderingSystem();
		m_FrameBuffer->UnBind();

		ImGui::Image((ImTextureID)m_FrameBuffer->GetRenderingID(), ImVec2{ p_WindowSize.x, p_WindowSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	}

	void SceneViewWindow::OnWindowResize(glm::vec2 windowSize)
	{
		m_FrameBuffer->Resize((uint32_t)windowSize.x, (uint32_t)windowSize.y);
	}
}