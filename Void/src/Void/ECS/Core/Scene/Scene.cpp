#include "pch.h"
#include "Scene.h"

namespace Void {
	Entity* Scene::CreateEntity()
	{
		entt::entity id = m_Registry.create();
		Entity* entity = new Entity(id, m_Registry, std::bind(&Scene::RemoveEntity, this, std::placeholders::_1));

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

	Entity* Scene::GetEntity(const entt::entity& id)
	{
		VOID_CORE_ASSERT(m_Entities.count(id), "No Entity bound to the given id.");
		return m_Entities[id];
	}

	void Scene::RemoveEntity(const entt::entity& id)
	{
		// Remove object
		delete GetEntity(id);
		// Remove entity
		m_Registry.destroy(id);
		// Remove from map
		m_Entities.erase(id);
	}
}