#pragma once

#include "pch.h"
#include "Window.h"
#include <Void/Event/WindowEvents.h>

namespace Void {

	class VOID_API Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning;

		bool CloseApplication(WindowCloseEvent& e);
	};

	Application* CreateApplication();

}
