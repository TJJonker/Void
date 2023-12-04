#include "SceneViewWindow.h"

namespace Nebula::Window {
	
	void SceneViewWindow::OnAdded()
	{
		p_Name = "Scene View";

		Void::Rendering::FrameBufferConfig config{1280, 720};
		m_FrameBuffer = Void::Rendering::FrameBuffer::Create(config);
		Void::Rendering::RenderingCommands::SetClearColor({ .1, .2, .1, 1 });

		m_EditorCamera = new EditorCamera(45.f, 1280.f / 720.f, .001f, 100.f);

		Void::Rendering::RenderingCommands::PrepareRender(m_EditorCamera, m_EditorCamera)
	}

	void SceneViewWindow::OnGuiRender()
	{
		m_FrameBuffer->Bind();
		Void::Rendering::RenderingCommands::Clear();
		Void::SceneManager::GetInstance().GetCurrentScene()->UpdateRenderingSystem();
		m_FrameBuffer->UnBind();

		ImGui::Image((ImTextureID)m_FrameBuffer->GetRenderingID(), ImVec2{ p_WindowSize.x, p_WindowSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	}

	void SceneViewWindow::OnWindowResize(glm::vec2 windowSize)
	{
		//m_FrameBuffer->Resize((uint32_t)windowSize.x, (uint32_t)windowSize.y);
	}
}