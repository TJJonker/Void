#include "pch.h"
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>

namespace Void {
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);

		glfwInit();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
	}


}