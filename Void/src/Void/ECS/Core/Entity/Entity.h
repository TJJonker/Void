#pragma once
#include <Void/Vendor/entt/entt.hpp>
#include "Void/ECS/Event/IECSEventInfo.h"
#include "Void/ECS/Event/ECSEventType.h"

namespace Void {
	class Entity {
	private:
		entt::entity m_Entity;
		entt::registry& m_Registry;

		std::map<ECSEventType, std::vector<IECSEventInfo>> m_Events;

	public:
		Entity(entt::entity entity, entt::registry& registry);
		
		template<typename T>
		T& AddComponent() {
			m_Registry.emplace<T>(m_Entity);
			return m_Registry.get<T>(m_Entity);
		}

		template<typename T>
		T& GetComponent() const {
			return m_Registry.get<T>(m_Entity);
		}

		template<typename T>
		bool HasComponent() const {
			return m_Registry.any_of<T>(m_Entity);
		}

		void RecordEvent(ECSEventType type, IECSEventInfo info);
		const std::map<ECSEventType, std::vector<IECSEventInfo>>& GetEvents() const;
		void ResetEvents();
	};
}