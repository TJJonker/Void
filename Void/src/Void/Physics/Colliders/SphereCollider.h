#pragma once
#include "Collider.h"

namespace Void {
	struct SphereCollider : public Collider {
	
		glm::vec3 Offset;
		float Radius;

		std::vector<CollisionPoint> TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const override;
		std::vector<CollisionPoint> TestCollision(const Transform* transform, const SphereCollider* collider, const Transform* sphereTransform) const override;
		std::vector<CollisionPoint> TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const override;
		std::vector<CollisionPoint> TestCollision(const Transform* transform, const MeshCollider* mesh, const Transform* meshTransform) const override;

		nlohmann::ordered_json ToJSON() const override;
		void FromJSON(const nlohmann::json& json) override;
	};
}