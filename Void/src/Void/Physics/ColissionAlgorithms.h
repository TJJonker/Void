#pragma once
#include "Void/Physics/CollisionPoints.h"
#include <Void/Physics/Colliders/SphereCollider.h>

namespace Void {
	namespace CollisionAlgorithms {
		CollisionPoints FindSphereSphereColissionPoints(
			const SphereCollider* a, const Transform* ta,
			const SphereCollider* b, const Transform* tb);

		CollisionPoints FindSpherePlaneCollisionPoints(
			const SphereCollider* a, const Transform* ta,
			const PlaneCollider* b,	 const Transform* tb);

		CollisionPoints FindPlaneSphereCollisionPoints(
			const PlaneCollider* a,  const Transform* ta,
			const SphereCollider* b, const Transform* tb);
	}
}

