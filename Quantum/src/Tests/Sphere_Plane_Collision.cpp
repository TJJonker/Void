#include "QuantumPch.h"
#include "Tests/Sphere_Plane_Collision.h"

namespace Quantum::Tests {
    std::vector<CollisionInfo> FindSpherePlaneCollisionPoints(const SphereCollider3D* colliderA, const glm::mat4& transformA, const PlaneCollider3D* colliderB, const glm::mat4& transformB)
    {
        std::vector<CollisionInfo> result;
        CollisionInfo info;

        glm::vec3 delta = transformA[3] - transformB[3];

        // Calculate the distance from the sphere center to the plane
        float sphereToPlaneDistance = glm::abs(glm::dot(delta, colliderB->Normal));

        if (sphereToPlaneDistance <= colliderA->Radius) {
            glm::vec3 intersectionPoint = (glm::vec3)transformA[3] - sphereToPlaneDistance * colliderB->Normal;

            if (glm::abs(intersectionPoint.x - transformB[3].x) <= colliderB->HalfExtents.x &&
                glm::abs(intersectionPoint.y - transformB[3].y) <= colliderB->HalfExtents.y) {

                info.CollisionPosition = intersectionPoint;
                info.Normal = glm::normalize(delta);
                info.Depth = glm::abs(sphereToPlaneDistance - colliderA->Radius);
                result.push_back(info);
            }
        }

        return result;
    }
}
