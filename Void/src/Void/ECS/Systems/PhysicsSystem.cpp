#include "pch.h"
#include "PhysicsSystem.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/PhysicsComponent.h>
#include "Void/Utils/TimeSteps/Time.h"

namespace Void {
	void Void::PhysicsSystem::Update(entt::registry& registry)
	{
		for (entt::entity entity : registry.view<PhysicsComponent, TransformComponent>()) {
			auto& [transform, physics] = registry.get<TransformComponent, PhysicsComponent>(entity);

			physics.Force += physics.Mass * glm::vec3(0, -5, 0); // apply a force

			physics.Velocity += physics.Force / physics.Mass * Time::DeltaTime();
			transform.Position += physics.Velocity * Time::DeltaTime();

			physics.Force = glm::vec3(0, 0, 0); // reset net force at the end
		}
	}
}