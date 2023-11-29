#pragma once
#include "Windows/Core/GuiWindow.h"

namespace Nebula::Window {
	class SceneViewWindow : public GuiWindow
	{
		virtual void OnAdded() override;

		// Inherited via GuiWindow
		virtual void OnGuiRender() override;
	};
}

