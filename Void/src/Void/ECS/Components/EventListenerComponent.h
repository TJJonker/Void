#pragma once
#include "Void/Utils/Command/ICommand.h"
#include <Void/ECS/Event/ECSEventType.h>

namespace Void {
	struct EventListenerComponent {
		ECSEventType EventType;
		ICommand* Command;
	};
}