#include "QuantumPch.h"
#include "Tests/Sphere_Sphere_Collision.h"

namespace Quantum::Tests {
    std::vector<CollisionInfo> FindSphereSphereColissionPoints(const SphereCollider3D* colliderA, const glm::mat4& transformA, const SphereCollider3D* colliderB, const glm::mat4& transformB)
    {
        std::vector<CollisionInfo> result;
        CollisionInfo info;
        // Calculate the distance between the centers of the two spheres
        glm::vec3 delta = transformB[3] - transformA[3];
        float distance = glm::length(delta);

        // Check for collision by comparing the distance to the sum of the radii
        if (distance < (colliderA->Radius + colliderB->Radius)) {
            // Calculate the collision normal and depth
            glm::vec3 collisionNormal = glm::normalize(delta);
            float penetrationDepth = (colliderA->Radius + colliderB->Radius) - distance;

            // Fill in the CollisionPoints struct
            info.CollisionPosition = (glm::vec3)transformA[3] + (collisionNormal * colliderA->Radius);
            info.Normal = -collisionNormal;
            info.Depth = penetrationDepth;
            result.push_back(info);
        }

        return result;
    }
}