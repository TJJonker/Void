#include "SceneViewWindow.h"

namespace Nebula::Window {
	
	void SceneViewWindow::OnAdded()
	{
		p_Name = "Scene View";

		Void::Rendering::RenderingCommands::Initialize();

		Void::Rendering::FrameBufferConfig config{1920, 1080};
		m_FrameBuffer = Void::Rendering::FrameBuffer::Create(config);
		Void::Rendering::RenderingCommands::SetClearColor({ .3, .2, .2, 1 });

		m_EditorCamera = new EditorCamera(45.f, 1280.f / 720.f, .1f, 100.f);

	}

	void SceneViewWindow::OnGuiRender()
	{
		m_EditorCamera->OnUpdate();

		m_FrameBuffer->Bind();
		Void::Rendering::RenderingCommands::Clear();
		Void::SceneManager::GetInstance().GetCurrentScene()->UpdateRenderingSystem();
		Void::Rendering::RenderingCommands::PrepareRender(m_EditorCamera->GetViewProjection(), m_EditorCamera->GetPosition());
		Void::Rendering::RenderingCommands::Render();
		m_FrameBuffer->UnBind();

		ImGui::Image((ImTextureID)m_FrameBuffer->GetRenderingID(), ImVec2{ p_WindowSize.x, p_WindowSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		Void::Rendering::RenderingCommands::ResetSubmissions();
	}

	void SceneViewWindow::OnWindowResize(glm::vec2 windowSize)
	{
		//m_FrameBuffer->Resize((uint32_t)windowSize.x, (uint32_t)windowSize.y);
	}

	void SceneViewWindow::OnEvent(Void::Event& event)
	{
		m_EditorCamera->OnEvent(event);
	}
}