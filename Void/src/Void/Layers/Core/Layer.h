#pragma once
#include <Void/Event/Event.h>

namespace Void {
	class VOID_API Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAdded() {}
		virtual void OnRemoved() {}

		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		virtual void OnGuiRender() {}
	};
}
