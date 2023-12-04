#pragma once
#include <functional>
#include "MenuItem.h"
#include "Windows/Core/WindowManager.h"
#include "Void.h"

namespace Nebula::Window {
	class Menu
	{
	public:
		Menu(std::string menuName)
			: m_MenuName(menuName) { }

		void AddMenuItem(const char* label, std::function<void()> onClick, const char* shortCut = (const char*)0);
		void RenderMenu();
		void OnEvent(Void::Event& event);

	private:
		std::string m_MenuName;
		std::vector<MenuItem> m_MenuItems;
	};
}

