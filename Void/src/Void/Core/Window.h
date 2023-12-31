#pragma once
#include "pch.h"
#include <Void/Event/Event.h>

namespace Void {
		
	// Minimal requiresments 
	struct WindowProps {
		std::string WindowTitle;
		uint16_t Width;
		uint16_t Height;

		WindowProps(const std::string& windowTitle = "New Window", uint16_t width = 1920, uint16_t height = 1080)
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

		virtual void* GetWindow() const = 0;

		/// <summary>
		/// Creates a window, depending on the selected platform.
		/// </summary>
		/// <param name="props">Properties of the window.</param>
		/// <returns>A scoped version of the window.</returns>
		static Window* Create(const WindowProps& props = WindowProps());

		/// <summary>
		/// 
		/// </summary>
		using EventCallbackFunction = std::function<void(Event&)>;

		/// <summary>
		/// Forwards the events to the given callback function.
		/// </summary>
		/// <param name="callback">Callback to which the Event will be forwarded.</param>
		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
	};

}

