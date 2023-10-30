#include "pch.h"
#include "ColissionAlgorithms.h"

namespace Void {
    namespace CollisionAlgorithms {
        CollisionPoints FindSphereSphereColissionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
        {
            CollisionPoints result;

            // Calculate the distance between the centers of the two spheres
            glm::vec3 delta = tb->Position + b->Center - (ta->Position + a->Center);
            float distance = glm::length(delta);

            // Check for collision by comparing the distance to the sum of the radii
            if (distance <= (a->Radius + b->Radius)) {
                // Calculate the collision normal and depth
                glm::vec3 collisionNormal = glm::normalize(delta);
                float penetrationDepth = (a->Radius + b->Radius) - distance;

                // Fill in the CollisionPoints struct
                result.A = ta->Position + a->Center + a->Radius * collisionNormal;
                result.B = tb->Position + b->Center + b->Radius * collisionNormal;
                result.Normal = collisionNormal;
                result.Depth = penetrationDepth;
                result.HasCollision = true;
            }
            else {
                // No collision
                result.HasCollision = false;
            }

            return result;
        }

        CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider* a, const Transform* ta, const PlaneCollider* b, const Transform* tb)
        {
            return CollisionPoints();
        }

        CollisionPoints FindPlaneSphereCollisionPoints(const PlaneCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
        {
            return CollisionPoints();
        }
    }
}