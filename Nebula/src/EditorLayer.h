#pragma once
#include "Void.h"
#include "Windows/GeneralDockspace/GeneralDockspace.h"

namespace Nebula::Editor {
	class EditorLayer : public Void::Layer
	{
	public:
		void OnAdded() override;
		void OnUpdate() override;
		void OnGuiRender() override;

	private:
		Window::GeneralDockspace* m_Dockspace;
	};
}