#include "pch.h"
#include "IntroSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include <Void/ECS/Components/CameraComponent.h>
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/IntroTrigger.h>
#include <Void/Audio/AudioManager/AudioManager.h>

namespace Void {
	void IntroSystem::Update(Scene* scene)
	{
		Entity* playerEntity = scene->GetAllEntitesWith<CameraComponent, TransformComponent>()[0];
		Entity* triggerEntity = scene->GetAllEntitesWith<IntroTrigger, TransformComponent>()[0];

		TransformComponent& playerTransform = playerEntity->GetComponent<TransformComponent>();
		TransformComponent& triggerTransform = triggerEntity->GetComponent<TransformComponent>();
		IntroTrigger& trigger = triggerEntity->GetComponent<IntroTrigger>();

		float distance = glm::distance(playerTransform.Position, triggerTransform.Position);
		static unsigned int soundID;
		if (distance < trigger.DistanceToPlayer && !trigger.Entered) {
			trigger.Entered = true;
			soundID = Audio::AudioManager::GetInstance()->PlayAudio(trigger.SoundPath.c_str(), CHANNELGROUP_MASTER_INDEX);
			Audio::AudioManager::GetInstance()->AddChorusToChannel(soundID);
		}
		else if (distance > trigger.DistanceToPlayer && trigger.Entered) {
			trigger.Entered = false;
			if (Audio::AudioManager::GetInstance()->IsValid(soundID)) {
				Audio::AudioManager::GetInstance()->StopAudio(soundID);
			}
		}
	}
}