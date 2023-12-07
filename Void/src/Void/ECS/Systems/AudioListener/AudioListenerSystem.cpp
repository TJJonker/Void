#include "pch.h"
#include "AudioListenerSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/AudioListenerComponent.h>
#include <Void/ECS/Components/VelocityComponent.h>
#include <Void/ECS/Components/CameraComponent.h>
#include "Void/Audio/AudioManager/AudioManager.h"

namespace Void {
	void AudioListenerSystem::Update(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntitesWith<AudioListenerComponent, TransformComponent, CameraComponent, VelocityComponent>();
		VOID_ASSERT(entities.size() <= 1, "More than one active audioListener.");
		VOID_ASSERT(entities.size() >= 1, "No active audioListener.");

		Entity* entity = entities[0];
		
		AudioListenerComponent& audioListener = entity->GetComponent<AudioListenerComponent>();
		TransformComponent& transform = entity->GetComponent<TransformComponent>();
		CameraComponent& camera = entity->GetComponent<CameraComponent>();
		VelocityComponent& velocity = entity->GetComponent<VelocityComponent>();

		Audio::AudioManager::GetInstance()->SetListenerAttributes(transform.Position, velocity.Velocity, transform.GetForwardVector(), transform.GetUpVector());
	}
}