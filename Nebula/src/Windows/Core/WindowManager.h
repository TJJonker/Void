#pragma once
#include <string>
#include <map>
#include "GuiWindow.h"

namespace Nebula::Window {
	class WindowManager
	{
	public:
		void RenderWindows();

		void OpenWindow(std::string windowName);
		void CloseWindow(std::string windowName);
		void ToggleWindow(std::string windowName);

		bool IsOpen(std::string windowName);

		void AddWindow(std::string windowName, GuiWindow* window);

	private:
		std::map<std::string, GuiWindow*> m_Windows = {};
	};
}
