#pragma once
#include "Void.h"
#include <imgui.h>
#include "glm/glm.hpp"
#include <string>

namespace Nebula::Window {
	class GuiWindow
	{
	public:
		virtual void OnAdded() { }
		virtual void OnRemoved() { }
		void Render();

		virtual void OnEvent(Void::Event& event) {}

	protected:
		virtual void OnGuiRender() = 0;
		virtual void OnWindowResize(glm::vec2 windowSize) {}

		void SetFlags(ImGuiWindowFlags flags);
		void AddFlags(ImGuiWindowFlags flags);
		void RemoveFlags(ImGuiWindowFlags flags);

	private:
		void CheckAndApplyResize();

	public:
		bool IsOpen = false;

	protected:
		glm::vec2 p_WindowSize = glm::vec2(0);
		std::string p_Name = "New window";

	private:
		ImGuiWindowFlags m_Flags = ImGuiWindowFlags_None;
	};
}

