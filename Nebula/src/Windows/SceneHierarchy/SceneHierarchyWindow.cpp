#include "Void.h"
#include "SceneHierarchyWindow.h"

namespace Nebula::Window {
	void SceneHierarchyWindow::OnGuiRender()
	{
		std::vector<Void::Entity*> entities = Void::SceneManager::GetInstance().GetCurrentScene()->GetAllEntitesWith<Void::TransformComponent>();
		for (Void::Entity* entity : entities) {
			Void::TransformComponent& transform = entity->GetComponent<Void::TransformComponent>();
			ImGui::Text("Entity: %s", entity->Name.c_str());

			ImGui::DragFloat(("X##Entity_" + entity->Name).c_str(), &transform.Position.x);
			ImGui::DragFloat(("Y##Entity_" + entity->Name).c_str(), &transform.Position.y);
			ImGui::DragFloat(("Z##Entity_" + entity->Name).c_str(), &transform.Position.z);
		}
	}
}