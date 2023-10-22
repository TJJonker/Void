#include "pch.h"
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>
#include <Void/Event/WindowEvents.h>
#include <Void/Event/MouseEvents.h>

/// WindowsWindow is a window type used for windows. 
/// With the help of GLFW, we can create a window and render graphics inside this window. 

namespace Void {

	/// <summary>
	///  Whether GLFW has been initialized or not.
	/// </summary>
	static bool s_GLFWInitialized = false;

	/// <summary>
	/// Constructor for WindowsWindow.
	/// </summary>
	/// <param name="props">Window properties to adjust the created window.</param>
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	/// <summary>
	/// Destructor for WindowsWindow.
	/// </summary>
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	/// <summary>
	/// Intializes the window.
	/// </summary>
	/// <param name="props">Window properties to adjust the created window.</param>
	void WindowsWindow::Init(const WindowProps& props)
	{
		// Set window data.
		m_Data.Title = props.WindowTitle;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		VOID_CORE_INFO("Creating window {0} ({1}, {2})", props.WindowTitle, props.Width, props.Height);

		// Initialize GLFW if not intialized yet.
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			VOID_CORE_ASSERT(success, "Could not intialize GLFW!");
			s_GLFWInitialized = success;
		}
		
		// Create the window.
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		// Make the window the current context.
		glfwMakeContextCurrent(m_Window);
		// Set the data as user pointer for easy future access.
		glfwSetWindowUserPointer(m_Window, &m_Data);
		// Enabling VSync by default.
		SetVSync(true);

		// Register for the window's close event callback.
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
			});

		// Register for the window's mouse moved event callback.
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(x, y);
			data.EventCallback(event);
			});
	}

	/// <summary>
	/// Shuts down the window.
	/// </summary>
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	/// <summary>
	/// Updates the window.
	/// </summary>
	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	/// <summary>
	///	Sets the VSync option.
	/// </summary>
	/// <param name="enabled">Whether vsync is enabled or not.</param>
	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

	/// <summary>
	/// Returns whether VSync is enabled or not.
	/// </summary>
	/// <returns>Whether VSync is enabled or not.</returns>
	bool WindowsWindow::IsVSyncEnabled() const
	{
		return m_Data.VSync;
	}
}