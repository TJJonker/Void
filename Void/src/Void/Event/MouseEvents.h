#pragma once

#include "Event.h"

namespace Void {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(const uint16_t x, const uint16_t y)
			: x(x), y(y) {}

		uint16_t GetX() const { return x; }
		uint16_t GetY() const { return y; }

		EVENT_CLASS_TYPE(MouseMoved);

	private:
		uint16_t x, y;
	};
}