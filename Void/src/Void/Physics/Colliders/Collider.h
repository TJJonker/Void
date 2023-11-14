#pragma once
#include <Void/Physics/CollisionPoints.h>
#include <Void/Physics/Tranform.h>
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {

	struct SphereCollider;
	struct PlaneCollider;
	struct MeshCollider;

	struct Collider : public ISerializable {
	public:
		virtual std::vector<CollisionPoint> TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const = 0;
		virtual std::vector<CollisionPoint> TestCollision(const Transform* transform, const SphereCollider* collider, const Transform* sphereTransform) const = 0;
		virtual std::vector<CollisionPoint> TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const = 0;
		virtual std::vector<CollisionPoint> TestCollision(const Transform* transform, const MeshCollider* mesh, const Transform* meshTransform) const = 0;

		virtual nlohmann::ordered_json ToJSON() const = 0;
		virtual void FromJSON(const nlohmann::json& json) = 0;
	};
}