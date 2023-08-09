#pragma once

#include "Event.h"
#include <sstream>

namespace Void {
	class VOID_API KeyEvent : public Event {

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class VOID_API KeyPressedEvent : public KeyEvent {

	};
	
}