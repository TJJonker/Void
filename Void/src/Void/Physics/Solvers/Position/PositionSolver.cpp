#include "pch.h"
#include "PositionSolver.h"

namespace Void {
	void PositionSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision collision : collisions) {
            // Move the objects along the collision normal to resolve overlap
            float moveDistance = collision.CollisionPoint.Depth / (collision.aPhysics->IsStatic + collision.bPhysics->IsStatic); // Adjust as needed
			
			if (!collision.aPhysics->IsStatic) {
				collision.aTransform->Position += moveDistance * collision.CollisionPoint.Normal * 2.f;
			}
			
			if (!collision.bPhysics->IsStatic) {
				collision.bTransform->Position += moveDistance * collision.CollisionPoint.Normal * 2.f;
			}
		}
	}
}
