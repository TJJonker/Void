#include "pch.h"
#include "AudioListenerSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/AudioListenerComponent.h>

namespace Void {
	void AudioListenerSystem::Update(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntitesWith<AudioListenerComponent, TransformComponent>();
		VOID_ASSERT(entities.size() <= 1, "More than one active audioListener.");

		for (Entity* entity : entities) {
			AudioListenerComponent& audioListener = entity->GetComponent<AudioListenerComponent>();
			TransformComponent& transform = entity->GetComponent<TransformComponent>();


		}
	}
}