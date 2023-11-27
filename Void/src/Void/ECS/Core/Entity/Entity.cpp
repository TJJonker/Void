#include "pch.h"
#include "Entity.h"

namespace Void {
	Entity::Entity(entt::entity entity, entt::registry& registry)
		: m_Entity(entity), m_Registry(registry) { }
	
	void Entity::RecordEvent(ECSEventType type, IECSEventInfo info)
	{
		m_Events[type].push_back(info);
	}

	const std::map<ECSEventType, std::vector<IECSEventInfo>>& Entity::GetEvents() const
	{
		return m_Events;
	}

	void Entity::ResetEvents()
	{
		m_Events.clear();
	}
}