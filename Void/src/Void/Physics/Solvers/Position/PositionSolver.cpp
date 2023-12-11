#include "pch.h"
#include "PositionSolver.h"
#include <Void/ECS/Components/Physics/PhysicsComponent.h>
#include <Void/ECS/Components/TranformComponent.h>
#include "Void/ECS/Components/Physics/BoxCollider3DComponent.h"

namespace Void {
	void PositionSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision collision : collisions) {

			PhysicsComponent& aPhysics = collision.A->GetComponent<PhysicsComponent>();
			TransformComponent& aTransform = collision.A->GetComponent<TransformComponent>();
			BoxCollider3DComponent& aCollider = collision.A->GetComponent<BoxCollider3DComponent>();
			BoxCollider3DComponent& bCollider = collision.B->GetComponent<BoxCollider3DComponent>();

			PhysicsComponent& bPhysics = collision.B->GetComponent<PhysicsComponent>();
			TransformComponent& bTransform = collision.B->GetComponent<TransformComponent>();

			float aStatic = (float)aCollider.Collider.IsStatic();
			float bStatic = (float)bCollider.Collider.IsStatic();

			float scale = std::max(1.f, aStatic + bStatic);
			glm::vec3 rawResolution = collision.CollisionPoint.Normal * collision.CollisionPoint.Depth;
			glm::vec3 resolution = rawResolution / scale;

			
			aTransform.Position -= resolution * (1.f - aStatic);
			bTransform.Position += resolution * (1.f - bStatic);
		}
	}
}
