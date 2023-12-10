#include "Quantum/QuantumPch.h"
#include "Quantum/Tests/Sphere_Sphere_Collision.h"

namespace Quantum::Tests {
    std::vector<CollisionInfo> FindSphereSphereColissionPoints(const ICollider* colliderA, const glm::mat4& transformA, const ICollider* colliderB, const glm::mat4& transformB)
    {
        assert(colliderA->GetType() == ColliderType::Sphere);
        assert(colliderB->GetType() == ColliderType::Sphere);

        const SphereCollider3D* sphereColliderA = dynamic_cast<const SphereCollider3D*>(colliderA);
        const SphereCollider3D* sphereColliderB = dynamic_cast<const SphereCollider3D*>(colliderB);

        glm::mat4 sphereTransformA = glm::translate(transformA, sphereColliderA->GetOffset());
        glm::mat4 sphereTransformB = glm::translate(transformB, sphereColliderB->GetOffset());

        std::vector<CollisionInfo> result;
        CollisionInfo info;
        // Calculate the distance between the centers of the two spheres
        glm::vec3 delta = sphereTransformB[3] - sphereTransformA[3];
        float distance = glm::length(delta);

        // Check for collision by comparing the distance to the sum of the radii
        if (distance < (sphereColliderA->Radius + sphereColliderB->Radius)) {
            // Calculate the collision normal and depth
            glm::vec3 collisionNormal = glm::normalize(delta);
            float penetrationDepth = (sphereColliderA->Radius + sphereColliderB->Radius) - distance;

            // Fill in the CollisionPoints struct
            info.CollisionPosition = (glm::vec3)sphereTransformA[3] + (collisionNormal * sphereColliderA->Radius);
            info.Normal = -collisionNormal;
            info.Depth = penetrationDepth;
            result.push_back(info);
        }

        return result;
    }
}