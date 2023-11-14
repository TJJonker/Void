#include "pch.h"
#include "PlaneCollider.h"
#include "Void/Physics/ColissionAlgorithms.h"

namespace Void {
    std::vector<CollisionPoint> PlaneCollider::TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, transform);
    }

    std::vector<CollisionPoint> PlaneCollider::TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphereTransform) const
    {
        return CollisionAlgorithms::FindSpherePlaneCollisionPoints(sphere, sphereTransform, this, transform);
    }

    std::vector<CollisionPoint> PlaneCollider::TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const
    {
        VOID_ASSERT(false, "Not implemented yet");
        return { };
    }

    std::vector<CollisionPoint> PlaneCollider::TestCollision(const Transform* transform, const MeshCollider* mesh, const Transform* meshTransform) const
    {
        VOID_ASSERT(false, "Not implemented yet");
        return { };
    }

    nlohmann::ordered_json PlaneCollider::ToJSON() const
    {
        nlohmann::ordered_json json;
        json["Offset"]["X"] = Offset.x;
        json["Offset"]["Y"] = Offset.y;
        json["Offset"]["Z"] = Offset.z;

        json["Normal"]["X"] = Normal.x;
        json["Normal"]["Y"] = Normal.y;
        json["Normal"]["Z"] = Normal.z;

        json["HalfExtents"]["X"] = HalfExtents.x;
        json["HalfExtents"]["Y"] = HalfExtents.y;
        json["HalfExtents"]["Z"] = HalfExtents.z;
        return json;
    }

    void PlaneCollider::FromJSON(const nlohmann::json& json)
    {
        Offset.x = json["Offset"]["X"];
        Offset.y = json["Offset"]["Y"];
        Offset.z = json["Offset"]["Z"];

        Normal.x = json["Normal"]["X"];
        Normal.y = json["Normal"]["Y"];
        Normal.z = json["Normal"]["Z"];

        HalfExtents.x = json["HalfExtents"]["X"];
        HalfExtents.y = json["HalfExtents"]["Y"];
        HalfExtents.z = json["HalfExtents"]["Z"];
    }

}