#pragma once
#include <string>
#include <functional>

namespace Nebula::Window {
	struct MenuItem {	
		const char* label;
		std::function<void()> onClick;
		const char* ShortCut;

		MenuItem(const char* _label, std::function<void()> _onClick, const char* shortcut = (const char*)0)
			: label(_label), onClick(_onClick), ShortCut(shortcut) {}
	};
}