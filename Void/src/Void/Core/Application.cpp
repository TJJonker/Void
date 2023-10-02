#include "pch.h"
#include "Application.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace Void {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());

	}
	
	Application::~Application()
	{
	}

	void Application::Run() {
		while (true) {
		}
	}
}

