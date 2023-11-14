#pragma once
#include "Collider.h"
#include <Void/Physics/CollisionPoints.h>
#include <Void/Physics/Tranform.h>

namespace Void {
	struct PlaneCollider : public Collider {
		glm::vec3 Offset = glm::vec3(0);
		glm::vec3 Normal = glm::vec3(0, 1, 0);
		glm::vec3 HalfExtents = glm::vec3(1);

		std::vector<CollisionPoint> TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const override;
		std::vector<CollisionPoint> TestCollision(const Transform* transform, const SphereCollider* collider, const Transform* sphereTransform) const override;
		std::vector<CollisionPoint> TestCollision(const Transform* transform, const PlaneCollider* plane,const Transform* planeTransform) const override;
		std::vector<CollisionPoint> TestCollision(const Transform* transform, const MeshCollider* mesh, const Transform* meshTransform) const override;

		nlohmann::ordered_json ToJSON() const override;
		void FromJSON(const nlohmann::json& json) override;
	};
}