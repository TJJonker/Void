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

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: xOffset(xOffset), YOffset(yOffset) {}

		float GetXOffset() const { return xOffset; }
		float GetYOffset() const { return YOffset; }

		std::string ToString() const override { return "MouseScrolledEvent: " + std::to_string(GetXOffset()) + ", " + std::to_string(GetYOffset()); }

		EVENT_CLASS_TYPE(EventType::MouseScrolled);

	private:
		float xOffset, YOffset;
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