#pragma once
#include "pch.h"
#include <Void/Event/Event.h>

namespace Void {
		
	struct WindowProps {
		std::string WindowTitle;
		uint16_t Width;
		uint16_t Height;

		WindowProps(const std::string& windowTitle = "New Window", uint16_t width = 1280, uint16_t height = 720)
		: WindowTitle(windowTitle), Width(width), Height(height) { }
	};

	class Window
	{
	public:
		virtual ~Window() = default;
		virtual void OnUpdate() = 0;
		virtual uint16_t GetWidth() const = 0;
		virtual uint16_t GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());

		using EventCallbackFunction = std::function<void(Event&)>;
		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
	};

}

