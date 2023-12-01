#pragma once
#include "Windows/Core/GuiWindow.h"

namespace Nebula::Window {
	class InspectorWindow : public GuiWindow
	{
		// Inherited via GuiWindow
		virtual void OnGuiRender() override;
	};
}

