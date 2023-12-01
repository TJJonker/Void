#include "OpenWindowCommand.h"

namespace Nebula::Events {
	void OpenWindowCommand::Execute(EntitySelected& value)
	{
		m_WindowManager->OpenWindow(m_WindowName);
	}
}