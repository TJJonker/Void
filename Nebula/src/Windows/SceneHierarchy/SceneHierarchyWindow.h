#pragma once
#include "Windows/Core/GuiWindow.h"

namespace Nebula::Window {
	class SceneHierarchyWindow : public GuiWindow
	{
		virtual void OnGuiRender() override;
	};
}
