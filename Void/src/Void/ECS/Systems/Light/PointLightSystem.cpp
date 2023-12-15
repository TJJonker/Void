#include "pch.h"
#include "PointLightSystem.h"

#include "Void/ECS/Components/TranformComponent.h"
#include "Void/ECS/Components/PointLightComponent.h"
#include "Void/ECS/Components/SpotLightComponent.h"

#include "Void/ECS/Core/Scene/Scene.h"
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"

namespace Void {
	void PointLightSystem::Update(Scene* scene)
	{
		static float time = 0;
		time += Time::DeltaTime() * 2;
		if (time >= 1)
			time -= 1;

		std::vector<Entity*> entities = scene->GetAllEntitesWith<TransformComponent, PointLightComponent>();
		for (Entity* entity : entities) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			PointLightComponent& light = entity->GetComponent<PointLightComponent>();

			
			float constant = time * .1f;

			PointLightData pld = light.pointLightData;
			pld.Position = transform.Position;
			pld.Constant = constant;
			pld.Linear = .3f + constant / 20;
			Rendering::RenderingCommands::SubmitPointLight(pld);
		}

		std::vector<Entity*> entities2 = scene->GetAllEntitesWith<TransformComponent, SpotLightComponent>();
		for (Entity* entity : entities2) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			SpotLightComponent& light = entity->GetComponent<SpotLightComponent>();


			float constant = time * .1f;

			SpotLightData pld = light.SpotLightData;
			pld.Position = transform.Position;
			Rendering::RenderingCommands::SubmitSpotLight(pld);
		}
	}
}