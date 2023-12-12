#include "pch.h"
#include "PointLightSystem.h"

#include "Void/ECS/Components/TranformComponent.h"
#include "Void/ECS/Components/PointLightComponent.h"

#include "Void/ECS/Core/Scene/Scene.h"
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"

namespace Void {
	void PointLightSystem::Update(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntitesWith<TransformComponent, PointLightComponent>();
		for (Entity* entity : entities) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			PointLightComponent& light = entity->GetComponent<PointLightComponent>();

			light.pointLightData.Position = transform.Position;
			Rendering::RenderingCommands::SubmitPointLight(light.pointLightData);
		}
	}
}