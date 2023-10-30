#include "pch.h"
#include "SphereCollider.h"
#include "Void/Physics/ColissionAlgorithms.h"

namespace Void {
    CollisionPoints SphereCollider::TestCollision(
        const Transform* transform, 
        const Collider* collider, 
        const Transform* colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, transform);
    }

    CollisionPoints SphereCollider::TestCollision(
        const Transform* transform, 
        const SphereCollider* sphere, 
        const Transform* sphereTransform) const
    {
        return CollisionAlgorithms::FindSphereSphereColissionPoints(
            this, transform, sphere, sphereTransform);
    }

    CollisionPoints SphereCollider::TestCollision(
        const Transform* transform, 
        const PlaneCollider* plane, 
        const Transform* planeTransform) const
    {
        return CollisionAlgorithms::FindSpherePlaneCollisionPoints(
            this, transform, plane, planeTransform);
    }
}