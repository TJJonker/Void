#pragma once

#include "pch.h"
#include "Window.h"
#include <Void/Event/WindowEvents.h>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Void/Rendering/Components/Shader/Shader.h"

namespace Void {

	/// <summary>
	/// Class functioning as the core of the application.
	/// </summary>
	class VOID_API Application {
	public:
		/// <summary>
		/// Constructor for Application.
		/// </summary>
		Application();

		/// <summary>
		/// Destructor for Application.
		/// </summary>
		virtual ~Application();

		/// <summary>
		/// Function receiving and running event related methods.
		/// </summary>
		/// <param name="e">Event that's delegated</param>
		void OnEvent(Event& e);

		/// <summary>
		/// Runs the application.
		/// </summary>
		void Run();

	private:
		/// <summary>
		/// Pointer to the created window.
		/// </summary>
		std::unique_ptr<Window> m_Window;

		/// <summary>
		/// Whether the application is running or not.
		/// </summary>
		bool m_IsRunning;

		/// <summary>
		/// Closes the application. Can only be addressed with an event.
		/// </summary>
		/// <param name="e">Reference to the event called to close the application.</param>
		/// <returns>True when successfull, false if failed.</returns>
		bool CloseApplication(WindowCloseEvent& e);



		//////////Temporary
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_Shader;
	};

	/// <summary>
	/// Creates the application.
	/// </summary>
	/// <returns>A pointer to the application.</returns>
	Application* CreateApplication();
}
