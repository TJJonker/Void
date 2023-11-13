#include "pch.h"
#include "PositionSolver.h"

namespace Void {
	void PositionSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision collision : collisions) {

			float aStatic = (float)collision.aPhysics->IsStatic;
			float bStatic = (float)collision.bPhysics->IsStatic;

			float scale = std::max(1.f, aStatic + bStatic);
			glm::vec3 rawResolution = collision.CollisionPoint.Normal * collision.CollisionPoint.Depth;
			glm::vec3 resolution = rawResolution / scale;

			if (!aStatic && !bStatic) {
				VOID_CORE_WARN("Position Solver");
				VOID_CORE_TRACE("Penetration depth: {0}", collision.CollisionPoint.Depth);

				float length = glm::length(collision.bTransform->Position - collision.aTransform->Position);
				VOID_CORE_TRACE("Distance between objects: {0}", length);

				glm::vec3 opa = collision.aTransform->Position;
				VOID_CORE_TRACE("Old position object A: {0}, {1}, {2}", opa.x, opa.y, opa.z);
			}

			collision.aTransform->Position -= resolution * (1.f - aStatic);
			
			if (!aStatic && !bStatic) {
				glm::vec3 npa = collision.aTransform->Position;
				VOID_CORE_TRACE("New position object A: {0}, {1}, {2}", npa.x, npa.y, npa.z);

				glm::vec3 opb = collision.bTransform->Position;
				VOID_CORE_TRACE("Old position object B: {0}, {1}, {2}", opb.x, opb.y, opb.z);
			}

			collision.bTransform->Position += resolution * (1.f - bStatic);

			if (!aStatic && !bStatic) {
				glm::vec3 npb = collision.bTransform->Position;
				VOID_CORE_TRACE("New position object B: {0}, {1}, {2}", npb.x, npb.y, npb.z);

				float length = glm::length(collision.bTransform->Position - collision.aTransform->Position);
				VOID_CORE_TRACE("Distance between objects: {0} \n", length);
			}
		}
	}
}
