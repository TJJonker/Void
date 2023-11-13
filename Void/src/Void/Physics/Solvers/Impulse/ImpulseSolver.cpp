#include "pch.h"
#include "ImpulseSolver.h"

namespace Void {
	void ImpulseSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision collision : collisions) {
			PhysicsComponent* aPhysics = collision.aPhysics;
			PhysicsComponent* bPhysics = collision.bPhysics;

			glm::vec3& aVel = !aPhysics->IsStatic ? aPhysics->Velocity : glm::vec3(0.0f);
			glm::vec3& bVel = !bPhysics->IsStatic ? bPhysics->Velocity : glm::vec3(0.0f);

			glm::vec3 rVel = bVel - aVel;
			float nSpd = glm::dot(rVel, collision.CollisionPoint.Normal);

			float aInvMass = !aPhysics->IsStatic ? 1/aPhysics->Mass : 0.0f;
			float bInvMass = !bPhysics->IsStatic ? 1/bPhysics->Mass : 0.0f;

			// Impulse

			// This is important for convergence
			// a negitive impulse would drive the objects closer together
			if (nSpd >= 0)
				continue;

			float j = -(1.0f) * nSpd / (aInvMass + bInvMass);

			glm::vec3 impluse = j * collision.CollisionPoint.Normal;

			if (!aPhysics->IsStatic) {
				glm::vec3 force = impluse * aInvMass;
				aPhysics->Velocity -= force + force * .5f;
			}

			if (!bPhysics->IsStatic) {
				glm::vec3 force = impluse * bInvMass;
				bPhysics->Velocity += force + force * .5f;
			}
			int i = 0;
		}
	}
}
