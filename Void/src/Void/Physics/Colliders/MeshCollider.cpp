#include "pch.h"
#include "MeshCollider.h"

namespace Void {
	std::vector<CollisionPoint> Void::MeshCollider::TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	std::vector<CollisionPoint> Void::MeshCollider::TestCollision(const Transform* transform, const SphereCollider* collider, const Transform* sphereTransform) const
	{
		VOID_ASSERT(false, "Not implemented");
		return { CollisionPoint() };
	}

	std::vector<CollisionPoint> Void::MeshCollider::TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const
	{
		VOID_ASSERT(false, "Not implemented");
		return { CollisionPoint() };
	}

	std::vector<CollisionPoint> Void::MeshCollider::TestCollision(const Transform* transform, const MeshCollider* mesh, const Transform* meshTransform) const
	{
		VOID_ASSERT(false, "Not implemented");
		return { CollisionPoint() };
	}

	nlohmann::ordered_json Void::MeshCollider::ToJSON() const
	{
		nlohmann::ordered_json json;
		json["MeshName"] = MeshName;
		return json;
	}

	void Void::MeshCollider::FromJSON(const nlohmann::json& json)
	{
		MeshName = json["MeshName"];
	}


}