#pragma once
#include "Windows/Core/GuiWindow.h"

namespace Nebula::Window {
	class SceneHierarchyWindow : public GuiWindow
	{
	public:
		virtual void OnAdded() override;
		virtual void OnGuiRender() override;

	private:
		unsigned int m_CurrentSelected = -1;
	};
}
