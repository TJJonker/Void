#include "pch.h"
#include "PlaneCollider.h"
#include "Void/Physics/ColissionAlgorithms.h"

namespace Void {
    CollisionPoints PlaneCollider::TestCollision(
        const Transform* transform, 
        const Collider* collider, 
        const Transform* colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, transform);
    }

    CollisionPoints PlaneCollider::TestCollision(
        const Transform* transform, 
        const SphereCollider* sphere, 
        const Transform* sphereTransform) const
    {
        return CollisionAlgorithms::FindPlaneSphereCollisionPoints(
            this, transform, sphere, sphereTransform);
    }

    CollisionPoints PlaneCollider::TestCollision(
        const Transform* transform, 
        const PlaneCollider* plane, 
        const Transform* planeTransform) const
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

        json["Extents"]["X"] = Extents.x;
        json["Extents"]["Y"] = Extents.y;
        json["Extents"]["Z"] = Extents.z;
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

        Extents.x = json["Extents"]["X"];
        Extents.y = json["Extents"]["Y"];
        Extents.z = json["Extents"]["Z"];
    }
}