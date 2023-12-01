#include "InspectorWindow.h"
#include "Events/Core/EventManager.h"
#include "Events/Commands/SetCurrentEntity/SetCurrentEntityCommand.h"

namespace Nebula::Window {
	void InspectorWindow::OnAdded()
	{
		p_Name = "Inspector";

		Events::EventManager::GetInstance().EntitySelectedEvent.AddCommand(new Events::SetCurrentEntityCommand(&m_SelectedEntity));
	}

	void InspectorWindow::OnGuiRender()
	{
		if (m_SelectedEntity == nullptr)
			return;

		Void::TransformComponent& transform = m_SelectedEntity->GetComponent<Void::TransformComponent>();

		ImGui::DragFloat3("Position", (float*)&transform.Position);
	}
}