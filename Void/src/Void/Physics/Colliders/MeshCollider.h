#pragma once
#include "Collider.h"

namespace Void {
	class MeshCollider : public Collider
	{
		// Inherited via Collider
		virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const override;
		virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* collider, const Transform* sphereTransform) const override;
		virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const override;

		virtual nlohmann::ordered_json ToJSON() const override;
		virtual void FromJSON(const nlohmann::json& json) override;
	};
}
