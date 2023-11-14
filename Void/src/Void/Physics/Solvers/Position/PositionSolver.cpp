#include "pch.h"
#include "PositionSolver.h"
#include <Void/ECS/Components/PhysicsComponent.h>
#include <Void/ECS/Components/TranformComponent.h>

namespace Void {
	void PositionSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision collision : collisions) {

			PhysicsComponent& aPhysics = collision.A->GetComponent<PhysicsComponent>();
			TransformComponent& aTransform = collision.A->GetComponent<TransformComponent>();

			PhysicsComponent& bPhysics = collision.B->GetComponent<PhysicsComponent>();
			TransformComponent& bTransform = collision.B->GetComponent<TransformComponent>();

			float aStatic = (float)aPhysics.IsStatic;
			float bStatic = (float)bPhysics.IsStatic;

			float scale = std::max(1.f, aStatic + bStatic);
			glm::vec3 rawResolution = collision.CollisionPoint.Normal * collision.CollisionPoint.Depth;
			glm::vec3 resolution = rawResolution / scale;

			
			aTransform.Position -= resolution * (1.f - aStatic);
			bTransform.Position += resolution * (1.f - bStatic);
		}
	}
}
