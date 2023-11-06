#pragma once
#include "Void/Layers/Core/Layer.h"

namespace Nebula::Editor {
	class EditorLayer : public Void::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		void OnAdded() override;
		void OnGuiRender() override;
	};
}

