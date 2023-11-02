#pragma once

#include "pch.h"
#include "Window.h"
#include <Void/Event/WindowEvents.h>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Void/Rendering/Components/Shader/Shader.h"
#include "Void/Rendering/Camera/CameraController/CameraController.h"
#include <Void/ECS/Core/Scene/Scene.h>
#include <Void/ImGui/ImGuiManager.h>
#include <Void/Layers/Layer.h>
#include <Void/Layers/LayerStack.h>


namespace Void {

	/// <summary>
	/// Class functioning as the core of the application.
	/// </summary>
	class VOID_API Application {
	private:
		// TODO: Remove 
		CameraController* m_CameraController; 

		Scene* m_Scene; 

		LayerStack m_LayerStack;

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

		static Application& Get();

		Window* GetWindow();

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
