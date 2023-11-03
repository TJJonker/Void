#pragma once

#include "Event.h"

namespace Void {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(const uint16_t x, const uint16_t y)
			: x(x), y(y) {}

		uint16_t GetX() const { return x; }
		uint16_t GetY() const { return y; }

		EVENT_CLASS_TYPE(EventType::MouseMoved);

		std::string ToString() const { return "MouseMovedEvent: " + std::to_string(x) + "," + std::to_string(y); }

	private:
		uint16_t x, y;
	};

	
	class MouseButtonPressedEvent : public Event {
	private:
		int m_Button;
	
	public:
		MouseButtonPressedEvent(int button)
			: m_Button(button) { }

		int GetButton() const { return m_Button; }

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed);
	};


	class MouseButtonReleasedEvent : public Event {
	private:
		int m_Button;

	public:
		MouseButtonReleasedEvent(int button)
			: m_Button(button) { }

		int GetButton() const { return m_Button; }

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased);
	};
}