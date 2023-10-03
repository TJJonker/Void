#pragma once
#include "pch.h"
#include <functional>

namespace Void {
	enum class EventType {
		None,
		WindowClose, WindowResize,
		MouseMoved
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
virtual const char* GetName() const override { return #type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }


	class Event {
	public:
		~Event() = default;

		bool IsHandled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

	class EventDispatcher {
	private:
		Event& m_Event;
	
	public:
		EventDispatcher(Event& event)
			: m_Event(event) { }

		template<typename T, typename F>
		bool Dispatch(const F& function) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.IsHandled |= function(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	};
}