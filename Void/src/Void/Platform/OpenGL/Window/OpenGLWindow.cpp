#include "pch.h"
#include "OpenGLWindow.h"
#include <Void/Event/WindowEvents.h>
#include <Void/Event/MouseEvents.h>
#include "Void/Platform/OpenGL/Input/OpenGLInput.h"

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
	OpenGLWindow::OpenGLWindow(const WindowProps& props)
	{
		Init(props);
	}

	/// <summary>
	/// Destructor for WindowsWindow.
	/// </summary>
	OpenGLWindow::~OpenGLWindow()
	{
		Shutdown();
	}

	/// <summary>
	/// Intializes the window.
	/// </summary>
	/// <param name="props">Window properties to adjust the created window.</param>
	void OpenGLWindow::Init(const WindowProps& props)
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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set major and minor version so it matches version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Switch to Core profile instead of Immediate mode
		
		// Create the window.
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		// Make the window the current context.
		glfwMakeContextCurrent(m_Window);

		m_RenderingContext.reset(RenderingContext::Create());
		m_RenderingContext->Init();

		Input::Create(m_Window);

		// TODO: (Re)move this.
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



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
	void OpenGLWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	/// <summary>
	/// Updates the window.
	/// </summary>
	void OpenGLWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	/// <summary>
	///	Sets the VSync option.
	/// </summary>
	/// <param name="enabled">Whether vsync is enabled or not.</param>
	void OpenGLWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

	/// <summary>
	/// Returns whether VSync is enabled or not.
	/// </summary>
	/// <returns>Whether VSync is enabled or not.</returns>
	bool OpenGLWindow::IsVSyncEnabled() const
	{
		return m_Data.VSync;
	}
}