#pragma once
#include "Void/Core/Window.h"
#include "Void/Rendering/Components/RenderingContext/RenderingContext.h"
#include <GLFW/glfw3.h>

namespace Void {

	class WindowsWindow : public Window
	{
	private: 
		GLFWwindow* m_Window;

		/// <summary>
		/// Struct containing base window data, that will also be passed with events.
		/// </summary>
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFunction EventCallback;
		};

		WindowData m_Data;
		std::shared_ptr<RenderingContext> m_RenderingContext;

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline uint16_t GetWidth() const override { return m_Data.Width; }
		inline uint16_t GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;
		
		void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};
}

