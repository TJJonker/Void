#pragma once

#include "pch.h"
#include "Window.h"
#include <Void/Event/WindowEvents.h>
#include <Void/ECS/Core/Scene/Scene.h>
#include <Void/Layers/Core/Layer.h>
#include <Void/Layers/Core/LayerStack.h>
#include "Void/Layers/ImGuiLayer.h"



namespace Void {

	/// <summary>
	/// Class functioning as the core of the application.
	/// </summary>
	class VOID_API Application {
	private:

		LayerStack m_LayerStack;

		ImGuiLayer* m_ImGuiLayer;

		/// <summary>
		/// Pointer to the created window.
		/// </summary>
		Window* m_Window;

		/// <summary>
		/// Whether the application is running or not.
		/// </summary>
		bool m_IsRunning = true;

		static Application* application; 

	private:
		/// <summary>
		/// Closes the application. Can only be addressed with an event.
		/// </summary>
		/// <param name="e">Reference to the event called to close the application.</param>
		/// <returns>True when successfull, false if failed.</returns>
		bool CloseApplication(WindowCloseEvent& e);

	public:
		/// <summary>
		/// Constructor for Application.
		/// </summary>
		Application();

		/// <summary>
		/// Destructor for Application.
		/// </summary>
		virtual ~Application();

		static Application& Get() { return *application; }

		Window* GetWindow() { return m_Window; }

		/// <summary>
		/// Function receiving and running event related methods.
		/// </summary>
		/// <param name="e">Event that's delegated</param>
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* layer);

		/// <summary>
		/// Runs the application.
		/// </summary>
		void Run();
	};

	/// <summary>
	/// Creates the application.
	/// </summary>
	/// <returns>A pointer to the application.</returns>
	Application* CreateApplication();
}
