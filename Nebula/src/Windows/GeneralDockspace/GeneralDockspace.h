#pragma once
#include <imgui.h>
#include <vector>
#include <Windows/Menus/Core/Menu.h>
#include <Windows/Core/WindowManager.h>

namespace Nebula::Window {
	class GeneralDockspace
	{
	public:
		void Initialize();
		void Render();

	private:
		void RenderContent();

	private:
		bool IsOpen = true;

		ImGuiViewport* m_Viewport;
		ImGuiWindowFlags m_Window_flags;

		std::vector<Menu*> m_MenuManagers;
		WindowManager* m_WindowManager;
	};
}
