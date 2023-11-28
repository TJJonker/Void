#include "pch.h"
#include "FootstepSystem.h"
#include <Void/ECS/Core/Scene/Scene.h>
#include <Void/ECS/Components/TranformComponent.h>
#include "Void/ECS/Components/FootstepComponent.h"
#include <Void/Audio/AudioManager/AudioManager.h>
#include <Void/Utils/Random/Random.h>

namespace Void {
	void FootstepSystem::Update(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntitesWith<TransformComponent, FootStepComponent>();

        for (Entity* entity : entities) {
            TransformComponent& transform = entity->GetComponent<TransformComponent>();
            FootStepComponent& footstep = entity->GetComponent<FootStepComponent>();

            // Calculate velocity based on the change in position over time
            glm::vec3 velocity = (transform.Position - footstep.LastStepPosition) / Time::DeltaTime();

            // Calculate the magnitude of the velocity
            float speed = glm::length(velocity);

            // Adjust the speed threshold based on your requirements
            float velocityThreshold = 1.f;

            footstep.TimeSinceLastStep += Time::DeltaTime();
            footstep.LastStepPosition = transform.Position;

            // Check if the entity is moving fast enough to trigger a footstep
            if (speed > velocityThreshold && footstep.TimeSinceLastStep > .6f) {
                footstep.IsLeft = !footstep.IsLeft;

                footstep.TimeSinceLastStep = 0;

                // Adjust the audio playback based on velocity or other parameters
                unsigned int soundIndex = Audio::AudioManager::GetInstance()->PlayAudio("Temp/Sound/footstep-gravel.wav", CHANNELGROUP_MASTER_INDEX);
                float offset = footstep.IsLeft ? -1.f : 1.f;
                glm::vec3 footOffset = glm::vec3(.5f, 0, 0) * offset;
                Audio::AudioManager::GetInstance()->SetChannelAttributes(soundIndex, transform.Position + glm::vec3(0, -.5f, 0) + footOffset, glm::vec3(0));
                Audio::AudioManager::GetInstance()->SetChannelPitch(soundIndex, Random::Between(.85f, 1.15f));

            }
        }
	}
}