#include "pch.h"
#include "ImpulseSolver.h"
#include <Void/ECS/Components/PhysicsComponent.h>
#include <Void/ECS/Components/VelocityComponent.h>

namespace Void {
	void ImpulseSolver::Solve(std::vector<Collision>& collisions)
	{
		for (Collision& collision : collisions) {
			
			PhysicsComponent& aPhysics = collision.A->GetComponent<PhysicsComponent>();
			PhysicsComponent& bPhysics = collision.B->GetComponent<PhysicsComponent>();

			VelocityComponent& aVelocity = collision.A->GetComponent<VelocityComponent>();
			VelocityComponent& bVelocity = collision.B->GetComponent<VelocityComponent>();

			float aStatic = (float)aPhysics.IsStatic;
			float bStatic = (float)bPhysics.IsStatic;

			glm::vec3 rVelocity = bVelocity.Velocity - aVelocity.Velocity;
			float nSpd = glm::dot(rVelocity, collision.CollisionPoint.Normal);

			float aInvMass = !aStatic ? 1 / aPhysics.Mass : 0.f;
			float bInvMass = !bStatic ? 1 / bPhysics.Mass : 0.f;

			if (nSpd >= 0)
				continue;

			//TODO: Introduce bounciness
			float bounciness = (/*!aStatic ? collision.aPhysics.bounciness : */0.7f) *
				(/*!bStatic ? collision.bPhysics.bounciness : */0.7f);

			float scale = -(1.0f + bounciness) * nSpd / (aInvMass + bInvMass);
			glm::vec3 impulse = scale * collision.CollisionPoint.Normal;

			if (!aStatic)
				aVelocity.Velocity -= impulse * aInvMass;

			if (!bStatic)
				bVelocity.Velocity += impulse * bInvMass;
		}
	}
}
