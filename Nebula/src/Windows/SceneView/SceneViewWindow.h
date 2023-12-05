#pragma once
#include "Void.h"
#include "Windows/Core/GuiWindow.h"
#include <Camera/EditorCamera.h>


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
	};
}

