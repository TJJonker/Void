#include "Menu.h"
#include <imgui.h>

namespace Nebula::Window {
	void Menu::AddMenuItem(const char* label, std::function<void()> onClick)
	{
		m_MenuItems.push_back({ label, onClick });
	}

	void Menu::RenderMenu()
	{
		if (ImGui::BeginMenu(m_MenuName.c_str())) {
			for (const MenuItem menuItem : m_MenuItems) {
				if (ImGui::MenuItem(menuItem.label)) {
					menuItem.onClick();
				}
			}
			ImGui::EndMenu();
		}
	}
}