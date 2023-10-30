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
        return { };
    }
}