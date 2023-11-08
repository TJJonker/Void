#include "pch.h"
#include "Scene.h"

namespace Void {
	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::UpdateSystems()
	{
		for (std::shared_ptr<ISystem> system : m_Systems)
			system->Update(m_Registry);
	}

	std::vector<entt::entity> Scene::GetAllEntities() const
	{
		std::vector<entt::entity> entities;
		for (entt::entity entity : m_Registry.view<entt::entity>()) {
			entities.push_back(entity);
		}
		return entities;
	}
}