#include "PlayerSystem.h"
#include <Void.h>

void PlayerSystem::Update(entt::registry& registry)
{
	for (entt::entity entity : registry.view<Void::TagComponent, Void::TransformComponent, Void::PhysicsComponent>()) {
		auto& [tag, transform, physics] = registry.get<Void::TagComponent, Void::TransformComponent, Void::PhysicsComponent>(entity);

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
