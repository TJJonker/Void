#pragma once
#include "Void/Layers/Core/Layer.h"
#include <Void/Event/MouseEvents.h>


namespace Void {

	class VOID_API ImGuiLayer : public Layer
	{
	public:
		void OnAdded() override;
		void OnRemoved() override;

		void OnGuiRender() override;

		void StartRendering();
		void EndRendering();
	};
}
