#pragma once
#include "Void.h"
#include "Windows/Core/GuiWindow.h"

namespace Nebula::Window {
	class InspectorWindow : public GuiWindow
	{
	public:
		virtual void OnAdded() override;
		virtual void OnGuiRender() override;

	private:
		void DrawTransformInspector();
		void DrawSpotLightInspector();
		void DrawPointLightInspector();
		void DrawBoxCollider3DComponent();

	private:
		Void::Entity* m_SelectedEntity = nullptr;
	};
}

