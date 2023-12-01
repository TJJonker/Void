#pragma once
#include <string>

namespace Nebula::Events {
	struct WindowOpened {
		std::string WindowName;
	};
}