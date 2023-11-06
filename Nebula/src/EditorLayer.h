#pragma once
#include "Void.h"

namespace Nebula::Editor {
	class EditorLayer : public Void::Layer
	{
	private:
		Void::Rendering::FrameBuffer* m_FrameBuffer;

	public:
		void OnAdded() override;
		void OnGuiRender() override;
	};
}

