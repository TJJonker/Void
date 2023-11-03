#include "pch.h"
#include "Window.h"

#ifdef VOID_PLATFORM_WINDOWS
	#include "Void/Platform/OpenGL/Window/OpenGLWindow.h"
#endif

namespace Void {

	Window* Window::Create(const WindowProps& props) {
#ifdef VOID_PLATFORM_WINDOWS
		return new OpenGLWindow(props);
#else
		VOID_CORE_ASSERT(false, "Unknown platform...");
		return nullptr;
#endif
	}
}