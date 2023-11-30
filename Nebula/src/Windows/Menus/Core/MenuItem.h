#pragma once
#include <string>
#include <functional>

namespace Nebula::Window {
	struct MenuItem {	
		const char* label;
		std::function<void()> onClick;

		MenuItem(const char* _label, std::function<void()> _onClick)
			: label(_label), onClick(_onClick) {}
	};
}