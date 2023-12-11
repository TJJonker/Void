#pragma once
#include <Void/ECS/Core/Systems/ISystem.h>
#include <Void/ECS/Core/Entity/Entity.h>

namespace Void {
	class Scene
	{
	private:
		entt::registry m_Registry;
		std::map<entt::entity, Entity*> m_Entities;

		std::shared_ptr<ISystem> m_RenderingSystem;
		std::shared_ptr<ISystem> m_PhysicsSystem;
		std::vector<std::shared_ptr<ISystem>> m_Systems;

	public:
		Entity* CreateEntity();

		~Scene();

		void AddSystem(std::shared_ptr<Void::ISystem> system) { m_Systems.push_back(system); }
		void UpdateSystems();

		void SetRenderingSystem(std::shared_ptr<Void::ISystem> system) { m_RenderingSystem = system; }
		void UpdateRenderingSystem() { m_RenderingSystem->Update(this); }

		void SetPhysicsSystem(std::shared_ptr<Void::ISystem> system) { m_PhysicsSystem = system; }
		void UpdatePhysicsSystem() { m_PhysicsSystem->Update(this); }

		std::vector<Entity*> GetAllEntities() const;
		
		Entity* GetEntity(uint32_t id);


		void RemoveEntity(const entt::entity& id);

		template<typename... T>
		std::vector<Entity*> GetAllEntitesWith() {
			entt::basic_view view = m_Registry.view<T...>();
			std::vector<Entity*> entities;

			for (entt::entity ent : view) {
				entities.push_back(GetEntity((uint32_t)ent));
			}

			return entities;
		}

		//entt::registry& Registry() { return m_Registry; }
	};
}

