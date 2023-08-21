#pragma once

#include "src/Void/Core.h"
#include <string>
#include <vector>
#include <functional>

namespace Void {

	enum class EventType {
		KeyPressed, KeyReleased,
		MousePressed, MouseReleased, MouseScrolled, MouseMoved,
		ApplicationExit, WindowResized
	};


	
	class Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
	private:
		bool m_Consumed = false;
	};

	class EventDispatcher {
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(std::function<bool(T&)> function) {
			static_assert(std::is_base_of<Event, T>::value, "T must be a subclass of Event");

			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.
			}
		}

	private:
		Event& m_Event;
	};
}