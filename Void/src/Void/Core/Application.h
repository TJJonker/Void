#pragma once

#include "pch.h"
#include "Window.h"

namespace Void {

	class VOID_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
	};

	Application* CreateApplication();

}
