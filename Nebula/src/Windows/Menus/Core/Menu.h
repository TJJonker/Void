#pragma once
#include <functional>
#include "MenuItem.h"

namespace Nebula::Window {
	class Menu
	{
	public:
		Menu(std::string menuName)
			: m_MenuName(menuName) { }

		void AddMenuItem(const char* label, std::function<void()> onClick);
		void RenderMenu();

	private:
		std::string m_MenuName;
		std::vector<MenuItem> m_MenuItems;
	};
}

