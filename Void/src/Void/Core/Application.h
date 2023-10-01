#pragma once

#include "pch.h"

namespace Void {

	class VOID_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}
