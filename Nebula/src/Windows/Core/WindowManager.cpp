#include <Void.h>
#include "WindowManager.h"
#include "Events/Core/EventManager.h"
#include "Events/Commands/OpenWindow/OpenWindowCommand.h"

namespace Nebula::Window {
	WindowManager::WindowManager()
	{
		Events::EventManager::GetInstance().EntitySelectedEvent.AddCommand(new Events::OpenWindowCommand("Inspector", this));
	}

	void WindowManager::RenderWindows()
	{
		for (auto const& window : m_Windows)
			window.second->Render();

		if (m_DemoWindowOpen)
			ImGui::ShowDemoWindow(&m_DemoWindowOpen);
	}

	void WindowManager::OpenWindow(std::string windowName)
	{
		VOID_ASSERT(m_Windows.count(windowName), "No window found called: '{0}'.", windowName);
		m_Windows[windowName]->IsOpen = true;
	}

	void WindowManager::CloseWindow(std::string windowName)
	{
		VOID_ASSERT(m_Windows.count(windowName), "No window found called: '{0}'.", windowName);
		m_Windows[windowName]->IsOpen = false;
	}

	void WindowManager::ToggleWindow(std::string windowName)
	{
		VOID_ASSERT(m_Windows.count(windowName), "No window found called: '{0}'.", windowName);
		m_Windows[windowName]->IsOpen = m_Windows[windowName]->IsOpen;
	}

	bool WindowManager::IsOpen(std::string windowName)
	{
		VOID_ASSERT(m_Windows.count(windowName), "No window found called: '{0}'.", windowName);
		return m_Windows[windowName]->IsOpen;
	}

	void WindowManager::AddWindow(std::string windowName, GuiWindow* window)
	{
		VOID_ASSERT(!m_Windows.count(windowName), "List already contains a window called: '{0}'", windowName);
		m_Windows[windowName] = window;
		window->OnAdded();
	}
}