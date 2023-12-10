#include "SceneViewWindow.h"
#include "Events/Core/EventManager.h"
#include "Events/Commands/SetCurrentEntity/SetCurrentEntityCommand.h"
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


		std::shared_ptr<Void::Rendering::RenderingSystem> renderingSystem = std::make_shared<Void::Rendering::RenderingSystem>();
		Void::SceneManager::GetInstance().GetCurrentScene()->SetRenderingSystem(renderingSystem);

		m_BroadPhase->SetDebugCallback([](const Quantum::AABB& aabb) {
			glm::vec3 center = (aabb.Min + aabb.Max) / 2.0f;

			// Calculate the extents (half-size) of the AABB
			glm::vec3 extents = (aabb.Max - aabb.Min) / 2.0f;

			// Create a translation matrix
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), center);

			// Create a scale matrix
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), extents);

			// Combine translation and scale to get the transformation matrix
			glm::mat4 transformMatrix = translationMatrix * scaleMatrix;

			Void::Rendering::RenderingCommands::SubmitDebugRectangle(transformMatrix, glm::vec4(0, 1, 0, 1));
			});
		std::shared_ptr<Void::PhysicsSystem> physicsSystem = std::make_shared<Void::PhysicsSystem>(m_Handler);
		Void::SceneManager::GetInstance().GetCurrentScene()->SetPhysicsSystem(physicsSystem);
	}

	void SceneViewWindow::OnGuiRender()
	{
		m_EditorCamera->OnUpdate();

		Void::SceneManager::GetInstance().GetCurrentScene()->UpdatePhysicsSystem();

		m_FrameBuffer->Bind();
		Void::Rendering::RenderingCommands::Clear();
		Void::SceneManager::GetInstance().GetCurrentScene()->UpdateRenderingSystem();
		Void::Rendering::RenderingCommands::PrepareRender(m_EditorCamera->GetViewProjection(), m_EditorCamera->GetPosition(), m_EditorCamera->GetSkybox());
		
		std::vector<Void::Entity*> view = Void::SceneManager::GetInstance().GetCurrentScene()->GetAllEntitesWith<Void::TransformComponent, Void::BoxCollider3DComponent>();
		for (Void::Entity* entity : view) {
			Void::TransformComponent& transform = entity->GetComponent<Void::TransformComponent>();
			Void::BoxCollider3DComponent& collider = entity->GetComponent<Void::BoxCollider3DComponent>();

			glm::mat4 transformMatrix = glm::translate(transform.GetTransformNS(), collider.Collider.GetOffset());
			transformMatrix = glm::scale(transformMatrix, collider.Collider.HalfExtents);
			Void::Rendering::RenderingCommands::SubmitDebugRectangle(transformMatrix, glm::vec4(1, 0, 0, 1));
		}
		m_BroadPhase->VisualiseDebug();
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
		if (m_GyzmoType == ImGuizmo::OPERATION::ROTATE)
			snapValue = 45.f;

		float snapValues[3] = { snapValue, snapValue, snapValue };

		ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
			(ImGuizmo::OPERATION)m_GyzmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
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

		if (Void::Input::KeyDown(49))
			m_GyzmoType = ImGuizmo::OPERATION::TRANSLATE;
		if (Void::Input::KeyDown(50))
			m_GyzmoType = ImGuizmo::OPERATION::ROTATE;
		if (Void::Input::KeyDown(51))
			m_GyzmoType = ImGuizmo::OPERATION::SCALE;
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