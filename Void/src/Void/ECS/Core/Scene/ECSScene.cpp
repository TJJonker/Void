#include "pch.h"
#include "ECSScene.h"

namespace Void {
    EntityID ECSScene::CreateEntity()
    {
        return m_Scene.CreateEntity();
    }

    void ECSScene::DestroyEntity(EntityID id)
    {
        m_Scene.DestroyEntity(id);
    }

    void ECSScene::UpdateSystems()
    {
        for (std::shared_ptr<ISystem> system : m_Systems)
            system->Update(m_Scene);
    }

    void ECSScene::AddSystem(std::shared_ptr<ISystem> system)
    {
        m_Systems.push_back(system);
    }

    void ECSScene::SetRenderingSystem(std::shared_ptr<ISystem> system)
    {
        m_RenderingSystem = system;
    }

    void ECSScene::UpdateRenderingSystem()
    {
        m_RenderingSystem->Update(m_Scene);
    }
}