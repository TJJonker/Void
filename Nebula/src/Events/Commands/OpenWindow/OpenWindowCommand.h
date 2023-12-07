#pragma once
#include "Events/Core/IEventCommand.h"
#include "Events/EventStructs/EntitySelected.h"
#include "Windows/Core/WindowManager.h"


namespace Nebula::Events {
	class OpenWindowCommand : public IEventCommand<EntitySelected>
	{
	public:
		OpenWindowCommand(std::string windowName, Window::WindowManager* windowManager)
			:m_WindowName(windowName), m_WindowManager(windowManager) { }

		virtual void Execute(EntitySelected& value) override;
	
	private:
		std::string m_WindowName;
		Window::WindowManager* m_WindowManager;
	};
}

