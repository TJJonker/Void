#pragma once
#include "Collider.h"

namespace Void {
	struct SphereCollider : public Collider {
	
		glm::vec3 Center;
		float Radius;

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