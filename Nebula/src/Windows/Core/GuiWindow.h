#pragma once
#include <imgui.h>
#include "glm/glm.hpp"

namespace Nebula::Window {
	class GuiWindow
	{
	public:
		virtual void OnAdded() { }
		virtual void OnRemoved() { }
		void Render();

	protected:
		virtual void OnGuiRender() = 0;
		virtual void OnWindowResize(glm::vec2 windowSize) {}

		void SetFlags(ImGuiWindowFlags flags);
		void AddFlags(ImGuiWindowFlags flags);
		void RemoveFlags(ImGuiWindowFlags flags);

	private:
		void CheckAndApplyResize();

	public:
		bool IsOpen;

	private:
		ImGuiWindowFlags m_Flags;
		glm::vec2 m_WindowSize;
	};
}

