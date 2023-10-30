#pragma once
#include <Void/Physics/CollisionPoints.h>
#include <Void/Physics/Tranform.h>
#include "PlaneCollider.h"

namespace Void {
	struct Collider {
	public:
		virtual CollisionPoints TestCollision(
			const Transform* transform,
			const Collider* collider,
			const Transform* colliderTransform) const = 0;

		virtual CollisionPoints TestCollision(
			const Transform* transform,
			const SphereCollider* collider,
			const Transform* sphereTransform) const = 0;

		virtual CollisionPoints TestCollision(
			const Transform* transform,
			const PlaneCollider* plane,
			const Transform* planeTransform) const = 0;
	};
}