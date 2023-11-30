#include "GuiWindow.h"

namespace Nebula::Window {
	void GuiWindow::Render()
	{
		ImGui::Begin(p_Name.c_str(), &IsOpen, m_Flags);
		CheckAndApplyResize();
		OnGuiRender();
		ImGui::End();		
	}

	void GuiWindow::SetFlags(ImGuiWindowFlags flags)
	{
		m_Flags = flags;
	}

	void GuiWindow::AddFlags(ImGuiWindowFlags flags)
	{
		m_Flags |= flags;
	}

	void GuiWindow::RemoveFlags(ImGuiWindowFlags flags)
	{
		m_Flags &= ~flags;
	}

	void GuiWindow::CheckAndApplyResize()
	{
		glm::vec2 windowSize = *((glm::vec2*)&ImGui::GetContentRegionAvail());
		if (p_WindowSize != windowSize) {
			OnWindowResize(windowSize);
			p_WindowSize = windowSize;
		}
	}
}