#include "pch.h"
#include "MovingSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include "Void/ECS/Components/TranformComponent.h"
#include "Void/ECS/Components/MovingComponent.h"
#include "Void/Audio/AudioManager/AudioManager.h"

namespace Void {
	void Void::MovingSystem::Update(Scene* scene)
	{
		static bool firstTime = true;
		static unsigned int soundID;
		static glm::vec3 lastStepPosition;

		std::vector<Entity*> entities = scene->GetAllEntitesWith<TransformComponent, MovingComponent>();

		if (firstTime) {
			firstTime = false;
			soundID = Audio::AudioManager::GetInstance()->PlayAudio("Temp/Sound/crazy-indian-scream.mp3", CHANNELGROUP_MASTER_INDEX);
		}

		for (Entity* entity : entities) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			MovingComponent& moving = entity->GetComponent<MovingComponent>();

			float direction = moving.MovesRight ? 1 : -1;
			transform.Position += Time::DeltaTime() * glm::vec3(1, 0, 0) * direction;
			if (transform.Position.x > 5)
				moving.MovesRight = false;
			else if(transform.Position.x < -5)
				moving.MovesRight = true;
			VOID_TRACE("position.x: {0}", transform.Position.x);

			glm::vec3 velocity = glm::vec3(1, 0, 0) * moving.Speed * direction;
			lastStepPosition = transform.Position;
			Audio::AudioManager::GetInstance()->SetChannelAttributes(soundID, transform.Position, velocity);
		}
	}
}
