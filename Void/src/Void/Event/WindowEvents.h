#pragma once

#include "Event.h"

namespace Void {
	
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose);
	};
}