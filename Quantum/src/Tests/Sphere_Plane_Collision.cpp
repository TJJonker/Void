#include "QuantumPch.h"
#include "Tests/Sphere_Plane_Collision.h"

namespace Quantum::Tests {
    std::vector<CollisionInfo> FindSpherePlaneCollisionPoints(const ICollider* colliderA, const glm::mat4& transformA, const ICollider* colliderB, const glm::mat4& transformB)
    {
        assert(colliderA->GetType() == ColliderType::Sphere);
        assert(colliderB->GetType() == ColliderType::Plane);

        const SphereCollider3D* sphereCollider = dynamic_cast<const SphereCollider3D*>(colliderA);
        const PlaneCollider3D* planeCollider = dynamic_cast<const PlaneCollider3D*>(colliderB);

        glm::mat4 sphereTransform = glm::translate(transformA, sphereCollider->GetOffset());
        glm::mat4 planeTransform = glm::translate(transformB, planeCollider->GetOffset());

        std::vector<CollisionInfo> result;
        CollisionInfo info;

        glm::vec3 delta = sphereTransform[3] - planeTransform[3];

        // Calculate the distance from the sphere center to the plane
        float sphereToPlaneDistance = glm::abs(glm::dot(delta, planeCollider->Normal));

        if (sphereToPlaneDistance <= sphereCollider->Radius) {
            glm::vec3 intersectionPoint = (glm::vec3)sphereTransform[3] - sphereToPlaneDistance * planeCollider->Normal;

            if (glm::abs(intersectionPoint.x - planeTransform[3].x) <= planeCollider->HalfExtents.x &&
                glm::abs(intersectionPoint.y - planeTransform[3].y) <= planeCollider->HalfExtents.y) {

                info.CollisionPosition = intersectionPoint;
                info.Normal = glm::normalize(delta);
                info.Depth = glm::abs(sphereToPlaneDistance - sphereCollider->Radius);
                result.push_back(info);
            }
        }

        return result;
    }
}
