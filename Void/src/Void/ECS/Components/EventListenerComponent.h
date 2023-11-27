#pragma once
#include <Void/ECS/Event/ECSEventType.h>
#include "Void/ECS/Event/IECSCommand.h"

namespace Void {
	struct EventListenerComponent {
		std::map<ECSEventType, std::vector<IECSCommand*>> Events;
	};
}