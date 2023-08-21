#pragma once

#include "Event.h"
#include <sstream>

namespace Void {

	class KeyEvent : public Event {
	public:
		unsigned int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(unsigned int keyCode) : m_KeyCode(keyCode) {}
		unsigned int m_KeyCode;		
	};


	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {};

		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		
	private:
		int m_RepeatCount;
	};
}