#include "pch.h"
#include "PhysicsSystem.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/PhysicsComponent.h>
#include "Void/Utils/TimeSteps/Time.h"
#include "Void/Physics/Collision.h"
#include "Void/ECS/Core/Scene/Scene.h"

namespace Void {

	void PhysicsSystem::Update(Scene* scene)
	{
		for (unsigned int i = 0; i < m_Substeps; i++) {
			ApplyForces(scene);
			ResolveCollisions(scene);
		}
	}

	void PhysicsSystem::ResolveCollisions(Scene* scene)
	{
		std::vector<Collision> collisions;
		std::vector<Entity*> entities = scene->GetAllEntitesWith<PhysicsComponent, TransformComponent>();

		for (Entity* a : entities) {

			TransformComponent& aTransform = a->GetComponent<TransformComponent>();
			PhysicsComponent& aPhysics = a->GetComponent<PhysicsComponent>();

			for (Entity* b : entities) {
				if (a == b)
					break;

				TransformComponent& bTransform = b->GetComponent<TransformComponent>();
				PhysicsComponent& bPhysics = b->GetComponent<PhysicsComponent>();

				if (!aPhysics.Collider || !bPhysics.Collider)
					continue;
				
				Transform transformA = { aTransform.Position, aTransform.Rotation, aTransform.Scale }; 
				Transform transformB = { bTransform.Position, bTransform.Rotation, bTransform.Scale };
				std::vector<CollisionPoint> points = aPhysics.Collider->TestCollision(&transformA, bPhysics.Collider, &transformB);

				for (const CollisionPoint& cp : points) {
					if (cp.HasCollision) {
						Collision collision{ a, b, cp };

						if (aPhysics.collisionCallback)
							aPhysics.collisionCallback(collision);

						if (bPhysics.collisionCallback)
							bPhysics.collisionCallback(collision);

						collisions.push_back(collision);
					}
				}
			}
		}

		for (std::shared_ptr<Solver> solver : m_Solvers)
			solver->Solve(collisions);
	}

	void PhysicsSystem::ApplyForces(Scene* scene)
	{
		for (const Entity* entity : scene->GetAllEntitesWith<PhysicsComponent, TransformComponent>()) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			PhysicsComponent& physics = entity->GetComponent<PhysicsComponent>();

			if (physics.IsStatic)
				continue;

			physics.Force += physics.Mass * glm::vec3(0, -2.5, 0); // apply a force

			physics.Velocity += physics.Force / physics.Mass * (Time::DeltaTime() / m_Substeps);
			transform.Position += physics.Velocity * (Time::DeltaTime() / m_Substeps);

			physics.Force = glm::vec3(0, 0, 0); // reset net force at the end
		}
	}
}