#include "pch.h"
#include "SphereCollider.h"
#include "Void/Physics/ColissionAlgorithms.h"

namespace Void {
    std::vector<CollisionPoint> SphereCollider::TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, transform);
    }

    std::vector<CollisionPoint> SphereCollider::TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphereTransform) const
    {
        return CollisionAlgorithms::FindSphereSphereColissionPoints(this, transform, sphere, sphereTransform);
    }

    std::vector<CollisionPoint> SphereCollider::TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const
    {
        return CollisionAlgorithms::FindSpherePlaneCollisionPoints(this, transform, plane, planeTransform);
    }

    std::vector<CollisionPoint> SphereCollider::TestCollision(const Transform* transform, const MeshCollider* mesh, const Transform* meshTransform) const
    {
        return CollisionAlgorithms::FindSphereMeshCollisionPoints(this, transform, mesh, meshTransform);
    }

    nlohmann::ordered_json SphereCollider::ToJSON() const
    {
        nlohmann::ordered_json json;
        json["Offset"]["X"] = Offset.x;
        json["Offset"]["Y"] = Offset.y;
        json["Offset"]["Z"] = Offset.z;

        json["Radius"] = Radius;
        return json;
    }

    void SphereCollider::FromJSON(const nlohmann::json& json)
    {
        Offset.x = json["Offset"]["X"];
        Offset.y = json["Offset"]["Y"];
        Offset.z = json["Offset"]["Z"];

        Radius = json["Radius"];
    }
}