#include "pch.h"
#include "Window.h"
#include "Void/Platform/Windows/WindowsWindow.h"

namespace Void {
	static bool GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		//return new WindowsWindow(props);
		return nullptr;
	}
}