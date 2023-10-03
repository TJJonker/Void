#pragma once
#include "Void/Core/Window.h"
#include <GLFW/glfw3.h>

namespace Void {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline uint16_t GetWidth() const override { return m_Data.Width; }
		inline uint16_t GetHeight() const override { return m_Data.Height; }

		// Window attributes
		//inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;
		
		bool IsRunning() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			//EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}

