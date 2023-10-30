#pragma once
#include "Collider.h"
#include <Void/Physics/CollisionPoints.h>
#include <Void/Physics/Tranform.h>
#include "SphereCollider.h"

namespace Void {
	struct PlaneCollider : public Collider {

		glm::vec3 Plane;
		float Distance;

		CollisionPoints TestCollision(
			const Transform* transform,
			const Collider* collider,
			const Transform* colliderTransform) const override;

		CollisionPoints TestCollision(
			const Transform* transform,
			const SphereCollider* collider,
			const Transform* sphereTransform) const override;

		CollisionPoints TestCollision(
			const Transform* transform,
			const PlaneCollider* plane,
			const Transform* planeTransform) const override;
	};
}