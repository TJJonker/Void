#include "pch.h"
#include "GunSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include <Void/ECS/Components/GunComponent.h>
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/Audio/AudioManager/AudioManager.h>

namespace Void {
	void GunSystem::Update(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntitesWith<TransformComponent, GunComponent>();
		for (Entity* entity : entities) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			GunComponent& gun = entity->GetComponent<GunComponent>();

			gun.CooldownTimer += Time::DeltaTime();
			if (gun.CooldownTimer < gun.Cooldown)
				continue;

			gun.CooldownTimer = 0;
			unsigned int soundId = Audio::AudioManager::GetInstance()->PlayAudio(gun.SoundPath.c_str(), CHANNELGROUP_MASTER_INDEX);
			Audio::AudioManager::GetInstance()->SetChannelAttributes(soundId, transform.Position, glm::vec3(0));
			Audio::AudioManager::GetInstance()->AddReverbToChannel(soundId);

			//Entity* entity = scene->CreateEntity();
			//entity->AddComponent
		}
	}
}