#include "pch.h"
#include "PhysicsSystem.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/VelocityComponent.h>
#include <Void/ECS/Components/VelocityComponent.h>
#include "Void/ECS/Core/Scene/Scene.h"
#include "Void/ECS/Event/CollisionInfo.h"

#include "Void/ECS/Components/Components.h"

namespace Void {

	void PhysicsSystem::Update(Scene* scene)
	{
		//for (unsigned int i = 0; i < m_Substeps; i++) {
		ApplyForces(scene);
		ResolveCollisions(scene);
		//}
	}

	void PhysicsSystem::ResolveCollisions(Scene* scene)
	{
		std::vector<Quantum::ICollider*> colliders;
		std::vector<Entity*> entities = scene->GetAllEntitesWith<BoxCollider3DComponent, TransformComponent>();


		for (Entity* entity : entities) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			BoxCollider3DComponent& collider = entity->GetComponent<BoxCollider3DComponent>();
			collider.Collider.SetID(entity->GetID());
			collider.Collider.CalculateBoundingBox(transform.GetTransformNS());
			colliders.push_back(&collider.Collider);
		}

		std::vector<Quantum::CollisionPair> collisionPairs;
		m_Handler.RunBroadPhase(colliders, collisionPairs);

		std::vector<Collision> allInfo;

		for (Quantum::CollisionPair pair : collisionPairs) {
			Void::TransformComponent& t1 = scene->GetEntity(pair.ColliderA->GetID())->GetComponent<Void::TransformComponent>();
			Void::TransformComponent& t2 = scene->GetEntity(pair.ColliderB->GetID())->GetComponent<Void::TransformComponent>();			
			std::vector<Quantum::CollisionInfo> outInfo = m_Handler.RunNarrowPhase(pair.ColliderA, t1.GetTransformMatrix(), pair.ColliderB, t2.GetTransformMatrix());
			for (Quantum::CollisionInfo& info : outInfo)
				allInfo.push_back({ scene->GetEntity(pair.ColliderA->GetID()), scene->GetEntity(pair.ColliderB->GetID()), info});
		}

		m_Solver.Solve(allInfo);


		
		/*for (Entity* a : entities) {
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
						a->RecordEvent(ECSEventType::OnCollide, CollisionInfo(b, cp));
						b->RecordEvent(ECSEventType::OnCollide, CollisionInfo(a, cp));
						collisions.push_back({a, b, cp});
					}
				}
			}
		}

		for (std::shared_ptr<Solver> solver : m_Solvers)
			solver->Solve(collisions);*/
	}

	void PhysicsSystem::ApplyForces(Scene* scene)
	{
		for (const Entity* entity : scene->GetAllEntitesWith<PhysicsComponent, TransformComponent, VelocityComponent>()) {
			TransformComponent& transform = entity->GetComponent<TransformComponent>();
			PhysicsComponent& physics = entity->GetComponent<PhysicsComponent>();
			VelocityComponent& velocity = entity->GetComponent<VelocityComponent>();

			physics.Force += physics.Mass * glm::vec3(0, -2.5, 0); // apply a force

			velocity.Velocity += physics.Force / physics.Mass * (Time::DeltaTime() / m_Substeps);
			transform.Position += velocity.Velocity * (Time::DeltaTime() / m_Substeps);

			physics.Force = glm::vec3(0, 0, 0); // reset net force at the end
		}
	}
}