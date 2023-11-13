#include "pch.h"
#include "PhysicsSystem.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/PhysicsComponent.h>
#include "Void/Utils/TimeSteps/Time.h"
#include "Void/Physics/Collision.h"

namespace Void {

	void PhysicsSystem::Update(entt::registry& registry)
	{
		for (int i = 0; i < m_Substeps; i++) {
			ApplyForces(registry);
			ResolveCollisions(registry);
		}
	}

	void PhysicsSystem::ResolveCollisions(entt::registry& registry)
	{
		std::vector<Collision> collisions;
		entt::basic_view view = registry.view<PhysicsComponent, TransformComponent>();

		for (entt::entity a : view) {

			auto& [aTransform, aPhysics] = registry.get<TransformComponent, PhysicsComponent>(a);

			for (entt::entity b : view) {
				if (a == b)
					break;

				auto& [bTransform, bPhysics] = registry.get<TransformComponent, PhysicsComponent>(b);

				if (!aPhysics.Collider || !bPhysics.Collider)
					continue;
				
				Transform transformA = { aTransform.Position, aTransform.Rotation, aTransform.Scale }; 
				Transform transformB = { bTransform.Position, bTransform.Rotation, bTransform.Scale };
				std::vector<CollisionPoint> points = aPhysics.Collider->TestCollision(&transformA, bPhysics.Collider, &transformB);

				for (CollisionPoint cp : points) {
					if (cp.HasCollision) {
						Collision collision;
						collision.aPhysics = &aPhysics;
						collision.aTransform = &aTransform;
						collision.bPhysics = &bPhysics;
						collision.bTransform = &bTransform;
						collision.CollisionPoint = cp;
						collisions.emplace_back(collision);
					}
				}
			}
		}

		for (std::shared_ptr<Solver> solver : m_Solvers)
			solver->Solve(collisions);
	}

	void PhysicsSystem::ApplyForces(entt::registry& registry)
	{
		for (entt::entity entity : registry.view<PhysicsComponent, TransformComponent>()) {
			auto& [transform, physics] = registry.get<TransformComponent, PhysicsComponent>(entity);

			if (physics.IsStatic)
				continue;

			physics.Force += physics.Mass * glm::vec3(0, -2.5, 0); // apply a force

			physics.Velocity += physics.Force / physics.Mass * (Time::DeltaTime() / m_Substeps);
			transform.Position += physics.Velocity * (Time::DeltaTime() / m_Substeps);

			physics.Force = glm::vec3(0, 0, 0); // reset net force at the end
		}
	}
}