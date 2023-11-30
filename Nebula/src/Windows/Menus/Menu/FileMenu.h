#pragma once
#include "Windows/Menus/Core/Menu.h"

namespace Nebula::Window {
	class FileMenu : public Menu
	{
	public:
		FileMenu(std::string name) 
			: Menu(name) 
		{
			AddMenuItem("Test1", []() {});
		}
	};
}

