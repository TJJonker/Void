#include "pch.h"
#include "Window.h"

#ifdef VOID_PLATFORM_WINDOWS
	#include "Void/Platform/Windows/WindowsWindow.h"
#endif

namespace Void {

	Scope<Window> Window::Create(const WindowProps& props) {
#ifdef VOID_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		VOID_CORE_ASSERT(false, "Unknown platform...");
		return nullptr;
#endif
	}
}