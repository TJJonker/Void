#pragma once
#include "Void.h"
#include "Void/ECS/Core/Scene/SceneManager.h"

namespace Nebula::Editor {
	class EditorLayer : public Void::Layer
	{
	private:
		Void::Rendering::FrameBuffer* m_FrameBuffer;

		Void::SceneManager* m_SceneManager;

	public:
		void OnAdded() override;
		void OnUpdate() override;
		void OnGuiRender() override;
	};
}

