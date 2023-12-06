#include "SceneViewWindow.h"
#include "Events/Core/EventManager.h"
#include "Events/Commands/SetCurrentEntity/SetCurrentEntityCommand.h"
#include "ImGuizmo/ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>

namespace Nebula::Window {
	
	void SceneViewWindow::OnAdded()
	{
		p_Name = "Scene View";

		Void::Rendering::RenderingCommands::Initialize();

		Void::Rendering::FrameBufferConfig config{1920, 1080};
		m_FrameBuffer = Void::Rendering::FrameBuffer::Create(config);
		Void::Rendering::RenderingCommands::SetClearColor({ .3, .2, .2, 1 });

		m_EditorCamera = new EditorCamera(45.f, 1280.f / 720.f, .1f, 100.f);
		m_EditorCamera->SetSkybox("Default");

		Events::EventManager::GetInstance().EntitySelectedEvent.AddCommand(new Events::SetCurrentEntityCommand(&m_SelectedEntity));
	}

	void SceneViewWindow::OnGuiRender()
	{
		m_EditorCamera->OnUpdate();

		m_FrameBuffer->Bind();
		Void::Rendering::RenderingCommands::Clear();
		Void::SceneManager::GetInstance().GetCurrentScene()->UpdateRenderingSystem();
		Void::Rendering::RenderingCommands::PrepareRender(m_EditorCamera->GetViewProjection(), m_EditorCamera->GetPosition(), m_EditorCamera->GetSkybox());
		Void::Rendering::RenderingCommands::Render();
		m_FrameBuffer->Unbind();

		ImGui::Image((ImTextureID)m_FrameBuffer->GetRenderingID(), ImVec2{ p_WindowSize.x, p_WindowSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		Void::Rendering::RenderingCommands::ResetSubmissions();

		if (m_SelectedEntity == nullptr)
			return;

		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		const glm::mat4& cameraProjection = m_EditorCamera->GetProjection();
		glm::mat4 cameraView = m_EditorCamera->GetViewMatrix();

		Void::TransformComponent& tc = m_SelectedEntity->GetComponent<Void::TransformComponent>();
		glm::mat4 transform = tc.GetTransformMatrix();

		bool snap = Void::Input::KeyPressed(341); // Left control
		float snapValue = 0.5f; // Snap to 0.5m for translation/scale

		float snapValues[3] = { snapValue, snapValue, snapValue };

		ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
			ImGuizmo::OPERATION::ROTATE, ImGuizmo::LOCAL, glm::value_ptr(transform),
			nullptr, snap ? snapValues : nullptr);

		if (ImGuizmo::IsUsing())
		{
			glm::vec3 translation, rotation, scale;
			Void::Math::DecomposeTransform(transform, translation, rotation, scale);

			glm::vec3 deltaRotation = rotation - tc.Rotation;
			tc.Position = translation;
			tc.Rotation += deltaRotation;
			tc.Scale = scale;
		}
	}

	void SceneViewWindow::OnWindowResize(glm::vec2 windowSize)
	{
		// TODO: Research why blended colors fuck up on framebuffer resizing
		//m_FrameBuffer->Resize((uint32_t)windowSize.x, (uint32_t)windowSize.y);
		m_EditorCamera->SetViewportSize(windowSize);
	}

	void SceneViewWindow::OnEvent(Void::Event& event)
	{
		m_EditorCamera->OnEvent(event);
	}
}