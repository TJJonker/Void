#pragma once
#include "Collider.h"
#include <Void/Physics/CollisionPoints.h>
#include <Void/Physics/Tranform.h>

namespace Void {
	struct PlaneCollider : public Collider {

		glm::vec3 Offset = glm::vec3(0);
		glm::vec3 Normal = glm::vec3(0, 1, 0);
		glm::vec3 Extents = glm::vec3(1);

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


		virtual nlohmann::ordered_json ToJSON() const override;
		virtual void FromJSON(const nlohmann::json& json) override;
	};
}