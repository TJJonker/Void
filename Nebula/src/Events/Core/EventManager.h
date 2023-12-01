#pragma once
#include "Events/EventStructs/EntitySelected.h"
#include "Events/EventStructs/WindowOpened.h"
#include "Events/Core/Event.h"

namespace Nebula::Events {
	struct EventManager
	{
		Event<EntitySelected> EntitySelectedEvent;
		Event<WindowOpened> WindowOpenedEvent;

		static EventManager& GetInstance();
	};
}
