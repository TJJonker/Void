#pragma once
#include "Void/Layers/Core/Layer.h"
#include <Void/Event/MouseEvents.h>


namespace Void {

	class ImGuiLayer : public Layer
	{
	private:
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);

	public:
		void OnAdded() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	};
}
