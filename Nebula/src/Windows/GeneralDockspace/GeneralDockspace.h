#pragma once
#include <imgui.h>

namespace Nebula::Window {
	class GeneralDockspace
	{
	public:
		void Initialize();
		void Render();

	private:
		void RenderContent();

	private:
		ImGuiViewport* m_Viewport;
		bool IsOpen = true;
		ImGuiWindowFlags m_Window_flags;
	};
}
