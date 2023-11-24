#pragma once
#include <Void/Vendor/entt/entt.hpp>

namespace Void {
	class Entity {
	
		using DestroyCallback = std::function<void(const entt::entity& id)>;

	private:
		entt::entity m_Entity;
		entt::registry& m_Registry;
		DestroyCallback onDestroyCallback;

	public:
		Entity(entt::entity entity, entt::registry& registry, DestroyCallback destroyCallback);
		~Entity();

		void Destroy();
		
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
	};
}