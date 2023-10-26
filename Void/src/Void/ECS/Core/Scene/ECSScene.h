#pragma once
#include "Scene.h"
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class ECSScene
	{
	private:
		Scene m_Scene;

		std::vector<std::shared_ptr<ISystem>> m_Systems;
		std::shared_ptr<ISystem> m_RenderingSystem;

	public:
		EntityID CreateEntity();
		void DestroyEntity(EntityID id);

		template<typename T>
		T* AddComponent(EntityID id) {
			return m_Scene.AddComponent<T>(id);
		}

		template<typename T>
		void RemoveComponent(EntityID id) {
			m_Scene.RemoveComponent<T>(id);
		}

		void UpdateSystems();
		void AddSystem(std::shared_ptr<ISystem> system);

		void SetRenderingSystem(std::shared_ptr<ISystem> system);
		void UpdateRenderingSystem();
	};
}
