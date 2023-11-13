#include "pch.h"
#include "ImpulseSolver.h"

namespace Void {
	void ImpulseSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision& collision : collisions) {
			
			float aStatic = (float)collision.aPhysics->IsStatic;
			float bStatic = (float)collision.bPhysics->IsStatic;

			glm::vec3 aVelocity = collision.aPhysics->Velocity;
			glm::vec3 bVelocity = collision.bPhysics->Velocity;
			glm::vec3 rVelocity = bVelocity - aVelocity;
			float nSpd = glm::dot(rVelocity, collision.CollisionPoint.Normal);

			float aInvMass = !aStatic ? 1 / collision.aPhysics->Mass : 0.f;
			float bInvMass = !bStatic ? 1 / collision.bPhysics->Mass : 0.f;

			if (nSpd >= 0)
				continue;

			float bounciness = (/*!aStatic ? collision.aPhysics.bounciness : */0.7f) *
				(/*!bStatic ? collision.bPhysics.bounciness : */0.7f);

			float scale = -(1.0f + bounciness) * nSpd / (aInvMass + bInvMass);
			glm::vec3 impulse = scale * collision.CollisionPoint.Normal;



			//VOID_CORE_WARN("Impulse Solver");

			glm::vec3 ova = collision.aPhysics->Velocity;
			//VOID_CORE_TRACE("Old velocity object A: {0}, {1}, {2}", ova.x, ova.y, ova.z);
			if (!aStatic)
				collision.aPhysics->Velocity -= impulse * aInvMass;
			glm::vec3 nva = collision.aPhysics->Velocity;
			//VOID_CORE_TRACE("New velocity object A: {0}, {1}, {2}", nva.x, nva.y, nva.z);

			glm::vec3 ovb = collision.bPhysics->Velocity;
			//VOID_CORE_TRACE("Old velocity object B: {0}, {1}, {2}", ovb.x, ovb.y, ovb.z);
			if (!bStatic)
				collision.bPhysics->Velocity += impulse * bInvMass;
			glm::vec3 nvb = collision.bPhysics->Velocity;
			//VOID_CORE_TRACE("New velocity object B: {0}, {1}, {2} \n", nvb.x, nvb.y, nvb.z);
		}
	}
}
