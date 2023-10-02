#pragma once
#include "Void/Core/Window.h"

namespace Void {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

	private:
		virtual void Init(const WindowProps& props);
	};
}

