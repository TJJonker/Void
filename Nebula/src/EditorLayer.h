#pragma once
#include "Void.h"

namespace Nebula::Editor {
	class EditorLayer : public Void::Layer
	{
	private:
		Void::Rendering::FrameBuffer* m_FrameBuffer;

		Void::Scene* m_Scene;

		Void::CameraController* m_CameraController;

	public:
		void OnAdded() override;
		void OnUpdate() override;
		void OnGuiRender() override;
	};
}

