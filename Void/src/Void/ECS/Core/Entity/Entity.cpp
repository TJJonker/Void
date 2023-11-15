#include "pch.h"
#include "Entity.h"

namespace Void {
	Entity::Entity(entt::entity entity, entt::registry& registry)
		: m_Entity(entity), m_Registry(registry) { }
	
	Entity::~Entity()
	{
		Destroy();
	}

	void Entity::Destroy() { }
}