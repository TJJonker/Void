#pragma once

#include "pch.h"
#include "Window.h"
#include <Void/Event/WindowEvents.h>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Void/Rendering/Components/Shader/Shader.h"
#include "Void/Rendering/Camera/CameraController/CameraController.h"
#include <Void/ECS/Core/Scene/Scene.h>
#include <Void/ImGui/ImGuiManager.h>


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
		Window* m_Window;

		/// <summary>
		/// Whether the application is running or not.
		/// </summary>
		bool m_IsRunning = true;

		/// <summary>
		/// Closes the application. Can only be addressed with an event.
		/// </summary>
		/// <param name="e">Reference to the event called to close the application.</param>
		/// <returns>True when successfull, false if failed.</returns>
		bool CloseApplication(WindowCloseEvent& e);

		CameraController* m_CameraController;

		Scene* m_Scene;

		ImGuiManager* m_ImGuiManager;

		static Application* application;
	public:
		static Application& Get();
		Window* GetWindow();
	};

	/// <summary>
	/// Creates the application.
	/// </summary>
	/// <returns>A pointer to the application.</returns>
	Application* CreateApplication();
}
