#include "pch.h"
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>
#include <Void/Event/WindowEvents.h>
#include <Void/Event/MouseEvents.h>

namespace Void {

	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.WindowTitle;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		VOID_CORE_INFO("Creating window {0} ({1}, {2})", props.WindowTitle, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			VOID_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(x, y);
			data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const
	{
		return m_Data.VSync;
	}
}