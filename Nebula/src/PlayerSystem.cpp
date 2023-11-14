#include "PlayerSystem.h"
#include <Void.h>
#include <Void/ECS/Components/TagComponent.h>
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/PhysicsComponent.h>

void PlayerSystem::Update(Void::Scene* scene)
{
	for (Void::Entity* entity : scene->GetAllEntitesWith<Void::TagComponent, Void::TransformComponent, Void::PhysicsComponent>()) {

		Void::TagComponent& tag = entity->GetComponent<Void::TagComponent>();
		Void::TransformComponent& transform = entity->GetComponent<Void::TransformComponent>();
		Void::PhysicsComponent& physics = entity->GetComponent<Void::PhysicsComponent>();

		if (tag.Tag == "Player") {
			glm::vec3 lastPosition = transform.Position;

			transform.Position.x += (Void::Input::KeyPressed(262) - Void::Input::KeyPressed(263)) * 1 * Void::Time::DeltaTime();
			transform.Position.z += (Void::Input::KeyPressed(264) - Void::Input::KeyPressed(265)) * 1 * Void::Time::DeltaTime();
		
			physics.Velocity = (transform.Position - lastPosition) / Void::Time::DeltaTime();
		}

		if (tag.Tag == "Slider") {
			transform.Rotation.y += 20 * Void::Time::DeltaTime();
		}

		if (tag.Tag == "Slider2") {
			transform.Rotation.y += 80 * Void::Time::DeltaTime();
		}
	}
}
