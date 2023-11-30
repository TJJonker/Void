#include "Void.h"
#include "SceneHierarchyWindow.h"

namespace Nebula::Window {
	void SceneHierarchyWindow::OnGuiRender()
	{
		std::vector<Void::Entity*> entities = Void::SceneManager::GetInstance().GetCurrentScene()->GetAllEntitesWith<Void::TransformComponent>();
		for (Void::Entity* entity : entities) {
			Void::TransformComponent& transform = entity->GetComponent<Void::TransformComponent>();
			ImGui::Text("Entity: %s", entity->m_Name.c_str());

			ImGui::DragFloat("X##Entity", &transform.Position.x);
			ImGui::DragFloat("Y##Entity", &transform.Position.y);
			ImGui::DragFloat("Z##Entity", &transform.Position.z);
		}
	}
}