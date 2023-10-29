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
}