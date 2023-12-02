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

		char entityName[32];
		strcpy(entityName, m_SelectedEntity->Name.c_str());
		ImGui::InputText("EntityName", entityName, 32);
		entityName[strlen(entityName)] = NULL;
		m_SelectedEntity->Name = entityName;

		if(m_SelectedEntity->HasComponent<Void::TransformComponent>())
			DrawTransformInspector();

		//if (m_SelectedEntity->HasComponent<Void::TransformComponent>();
		//	DrawTransformInspector();
	}

	void InspectorWindow::DrawTransformInspector()
	{
		Void::TransformComponent& transform = m_SelectedEntity->GetComponent<Void::TransformComponent>();
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_None))
		{
			ImGui::DragFloat3("Position", (float*)&transform.Position);
			ImGui::DragFloat3("Rotation", (float*)&transform.Rotation);
			ImGui::DragFloat3("Scale", (float*)&transform.Scale);
		}

		
	}
}