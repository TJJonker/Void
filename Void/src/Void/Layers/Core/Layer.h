#pragma once
#include <Void/Event/Event.h>

namespace Void {
	class Layer
	{
	public:
		virtual void OnAdded() {}
		virtual void OnRemoved() {}

		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
	};
}
