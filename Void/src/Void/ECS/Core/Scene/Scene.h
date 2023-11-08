#pragma once
#include <Void/ECS/Core/Systems/ISystem.h>
#include "Void/Vendor/entt/entt.hpp"

namespace Void {
	class Scene
	{
	private:
		entt::registry m_Registry;

		std::shared_ptr<ISystem> m_RenderingSystem;
		std::vector<std::shared_ptr<ISystem>> m_Systems;

	public:
		entt::entity CreateEntity();

		template<typename T>
		T& AddComponent(entt::entity entity) {
			m_Registry.emplace<T>(entity);
			return m_Registry.get<T>(entity);
		}

		template<typename T>
		T& GetComponent(entt::entity entity) {
			return m_Registry.get<T>(entity);
		}

		template<typename T>
		bool HasComponent(entt::entity entity) {
			return m_Registry.any_of<T>(entity);
		}

		void AddSystem(std::shared_ptr<Void::ISystem> system) { m_Systems.push_back(system); }
		void UpdateSystems();
		void SetRenderingSystem(std::shared_ptr<Void::ISystem> system) { m_RenderingSystem = system; }
		void UpdateRenderingSystem() { m_RenderingSystem->Update(m_Registry); }

		std::vector<entt::entity> GetAllEntities() const;

		entt::registry& Registry() { return m_Registry; }
	};
}

