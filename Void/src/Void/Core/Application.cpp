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
		while (m_Window->IsRunning()) {
			glClearColor(.1, .2, .1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}

