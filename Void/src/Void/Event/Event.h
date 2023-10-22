#pragma once
#include "pch.h"
#include <functional>

namespace Void {

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return type; }\
virtual const char* GetName() const override { return #type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }

	/// <summary>
	/// Different kinds of basic event types.
	/// </summary>
	enum class EventType {
		None,
		WindowClose,
		MouseMoved
	};

	/// <summary>
	/// Base Event class.
	/// </summary>
	class Event {
	public:
		~Event() = default;

		virtual EventType GetEventType() const = 0;

		// Debugging purposes
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

	/// <summary>
	/// Class responsible for checking and delegating events.
	/// </summary>
	class EventDelegator {
	private:
		Event& m_Event;
	
	public:
		/// <summary>
		/// Constructor for EventDelegator.
		/// </summary>
		/// <param name="event"></param>
		EventDelegator(Event& event)
			: m_Event(event) { }


		/// <summary>
		/// Checks whether the events are the right type and delegates accordingly.
		/// </summary>
		/// <typeparam name="T">Type of Event.</typeparam>
		/// <typeparam name="F">Type of function that should be run.</typeparam>
		/// <param name="function">Function that should be run.</param>
		/// <returns></returns>
		template<typename T, typename F>
		void Delegate(const F& function) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				// Run the given function and forward the event.
				function(static_cast<T&>(m_Event));
			}
		}
	};
}