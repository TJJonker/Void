#include "Void.h"
#include "SceneHierarchyWindow.h"
#include "Events/Core/EventManager.h"
#include "Events/EventStructs/EntitySelected.h"

namespace Nebula::Window {
	void SceneHierarchyWindow::OnAdded()
	{
		p_Name = "Scene Hierarchy";
	}

	void SceneHierarchyWindow::OnGuiRender()
	{
		std::vector<Void::Entity*> entities = Void::SceneManager::GetInstance().GetCurrentScene()->GetAllEntities();

		for (Void::Entity* entity : entities) {

			ImGui::PushID(entity->GetID());
			if (ImGui::Selectable(entity->Name.c_str(), m_CurrentSelected == entity->GetID())) {
				if (m_CurrentSelected != entity->GetID()) {
					Events::EntitySelected es{ entity };
					Events::EventManager::GetInstance().EntitySelectedEvent.Trigger(es);
				}
				m_CurrentSelected = entity->GetID();
			}
			ImGui::PopID();
		}
	}
}

