#include "pch.h"
#include "PositionSolver.h"

namespace Void {
	void PositionSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision collision : collisions) {

			float aStatic = (float)collision.aPhysics->IsStatic;
			float bStatic = (float)collision.bPhysics->IsStatic;

			float scale = std::max(1.f, aStatic + bStatic);
			glm::vec3 resolution = collision.CollisionPoint.Normal
				* collision.CollisionPoint.Depth / scale;

			collision.aTransform->Position -= resolution * (1 - aStatic);
			collision.bTransform->Position += resolution * (1 - bStatic);
		}
	}
}
