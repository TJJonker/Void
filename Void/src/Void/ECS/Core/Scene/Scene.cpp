#include "pch.h"
#include "Scene.h"

namespace Void {
	Entity* Scene::CreateEntity()
	{
		entt::entity id = m_Registry.create();
		Entity* entity = new Entity(id, m_Registry);

		m_Entities[id] = entity;
		return entity;
	}

	Scene::~Scene()
	{
		for (const auto& entity : m_Entities) {
			RemoveEntity(entity.first);
		}
	}

	void Scene::UpdateSystems()
	{
		for (std::shared_ptr<ISystem> system : m_Systems)
			system->Update(this);
	}

	std::vector<Entity*> Scene::GetAllEntities() const
	{
		std::vector<Entity*> entities;
		for (const auto& pair : m_Entities) {
			entities.push_back(pair.second);
		}
		return entities;
	}

	Entity* Scene::GetEntity(uint32_t id)
	{
		VOID_CORE_ASSERT(m_Entities.count((entt::entity)id), "No Entity bound to the given id.");
		return m_Entities[(entt::entity)id];
	}

	void Scene::RemoveEntity(const entt::entity& id)
	{
		// Remove object
		delete GetEntity((uint32_t)id);
		// Remove entity
		m_Registry.destroy(id);
		// Remove from map
		m_Entities.erase(id);
	}
}