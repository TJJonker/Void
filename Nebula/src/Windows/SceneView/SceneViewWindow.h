#pragma once
#include "Void.h"
#include "Windows/Core/GuiWindow.h"
#include <Camera/EditorCamera.h>
#include "ImGuizmo/ImGuizmo.h"


namespace Nebula::Window {
	class SceneViewWindow : public GuiWindow
	{
	public:
		virtual void OnAdded() override;
		virtual void OnGuiRender() override;
		virtual void OnWindowResize(glm::vec2 windowSize) override;
		virtual void OnEvent(Void::Event& event) override;

	private:
		Void::Rendering::FrameBuffer* m_FrameBuffer = nullptr;
		EditorCamera* m_EditorCamera = nullptr;
		Void::Entity* m_SelectedEntity = nullptr;
		int m_GyzmoType = ImGuizmo::OPERATION::TRANSLATE;

		Quantum::BroadPhase::Octree* m_BroadPhase = new Quantum::BroadPhase::Octree({ glm::vec3(-20, -20, -20), glm::vec3(20, 20, 20) }, 8);
		Quantum::CollisionHandler m_Handler{ m_BroadPhase, new Quantum::NarrowPhase::DefaultNarrowPhase() };
	};
}

