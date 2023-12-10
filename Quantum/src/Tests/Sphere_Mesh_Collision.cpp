#include "Quantum/QuantumPch.h"
#include "Quantum/Tests/Sphere_Mesh_Collision.h"
#include <Quantum/DataStructs/ExtendedTriangle.h>

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSphereMeshCollisionPoints(const ICollider* colliderA, const glm::mat4& transformA, const ICollider* colliderB, const glm::mat4& transformB)
	{
        assert(colliderA->GetType() == ColliderType::Sphere);
        assert(colliderB->GetType() == ColliderType::Mesh);

        const SphereCollider3D* sphereCollider = dynamic_cast<const SphereCollider3D*>(colliderA);
        const MeshCollider3D* meshCollider = dynamic_cast<const MeshCollider3D*>(colliderB);

        std::vector<CollisionInfo> result;

        glm::mat4 sphereTransform = glm::translate(transformA, sphereCollider->GetOffset());
        glm::mat4 meshTransform = glm::translate(transformB, meshCollider->GetOffset());

        size_t arraySize = meshCollider->Colliders.size();
        std::vector<ExtendedTriangle> extendedTriangles(arraySize);

        for (int i = 0; i < arraySize; i++) {
            for (int j = 0; j < 3; j++) 
                extendedTriangles[i].Positions[j] = meshTransform * glm::vec4(meshCollider->Colliders[i].Positions[j], 1.f);

            // Calculate the normal of the scaled triangle
            glm::vec3 edge1 = extendedTriangles[i].Positions[1] - extendedTriangles[i].Positions[0];
            glm::vec3 edge2 = extendedTriangles[i].Positions[2] - extendedTriangles[i].Positions[0];
            extendedTriangles[i].Normal = glm::normalize(glm::cross(edge1, edge2));
        }

        // Iterate over every triangle an determine collision
        for (int i = 0; i < arraySize; i++) {
            CollisionInfo info;
            if (FindSphereTriangleCollisionPoints(sphereTransform, sphereCollider->Radius, extendedTriangles[i], info))
                result.push_back(info);
        }

        return result;
	}

    bool FindSphereTriangleCollisionPoints(const glm::mat4& sphereTransform, const float sphereRadius, const ExtendedTriangle& triangle, CollisionInfo& outInfo)
    {
        glm::vec3 v0 = triangle.Positions[0];
        glm::vec3 v1 = triangle.Positions[1];
        glm::vec3 v2 = triangle.Positions[2];

        // Project the sphere center onto the plane of the triangle
        float d = glm::dot(triangle.Normal, v0);
        float distance = glm::dot(triangle.Normal, (glm::vec3)sphereTransform[3]) - d;

        if (glm::abs(distance) > sphereRadius) 
            return false;

        // Calculate the point on the triangle closest to the sphere center
        glm::vec3 closestPoint = (glm::vec3)sphereTransform[3] - distance * triangle.Normal;

        // Check if the closest point is inside the triangle
        if (PointInTriangle(closestPoint, triangle, outInfo))
            return true;

        // Check if the sphere intersects with any triangle edge
        if (SphereTriangleEdgeIntersect(sphereTransform[3], sphereRadius, v0, v1, outInfo))
            return true;

        // Check if the sphere intersects with any triangle edge
        if (SphereTriangleEdgeIntersect(sphereTransform[3], sphereRadius, v1, v2, outInfo))
            return true;

        // Check if the sphere intersects with any triangle edge
        if (SphereTriangleEdgeIntersect(sphereTransform[3], sphereRadius, v2, v0, outInfo))
            return true;
    
        return false;
    }

    bool PointInTriangle(const glm::vec3& point, const ExtendedTriangle& triangle, CollisionInfo& outInfo)
    {
        glm::vec3 v0 = triangle.Positions[0];
        glm::vec3 v1 = triangle.Positions[1];
        glm::vec3 v2 = triangle.Positions[2];

        glm::vec3 barycentric = Barycentric(point, v0, v1, v2);

        // Check if the barycentric coordinates are within the valid range for a point inside the triangle
        bool collides = (barycentric.x >= 0.0f && barycentric.y >= 0.0f && barycentric.z >= 0.0f &&
            barycentric.x <= 1.0f && barycentric.y <= 1.0f && barycentric.z <= 1.0f);

        if (collides) {
            // Calculate the collision position using barycentric coordinates
            outInfo.CollisionPosition = barycentric.x * v0 + barycentric.y * v1 + barycentric.z * v2;
            
            glm::vec3 closestPoint = barycentric.x * v0 + barycentric.y * v1 + barycentric.z * v2;
            outInfo.Depth = glm::distance(point, closestPoint);

            // Calculate the normal vector of the triangle
            outInfo.Normal = triangle.Normal;

            return true;
        }

        return false;
    }

    bool SphereTriangleEdgeIntersect(const glm::vec3& spherePosition, const float sphereRadius, const glm::vec3& v0, const glm::vec3& v1, CollisionInfo& outInfo)
    {
        // Calculate the closest point on the edge to the sphere center
        glm::vec3 edgeDirection = glm::normalize(v1 - v0);
        glm::vec3 edgeToPoint = spherePosition - v0;
        float t = glm::dot(edgeToPoint, edgeDirection);
        glm::vec3 closestPoint;

        if (t < 0.0f)
            closestPoint = v0;
        else if (t > glm::length(v1 - v0))
            closestPoint = v1;
        else
            closestPoint = v0 + t * edgeDirection;

        // Check if the closest point is within the sphere
        if (glm::length2(spherePosition - closestPoint) <= (sphereRadius * sphereRadius)) {
            outInfo.CollisionPosition = closestPoint;
            outInfo.Normal = glm::normalize(spherePosition - closestPoint);
            outInfo.Depth = (sphereRadius - glm::length(spherePosition - closestPoint));
            return true;
        }

        return false;
    }


    glm::vec3 Barycentric(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
    {
        glm::vec3 v0 = b - a, v1 = c - a, v2 = p - a;
        float d00 = glm::dot(v0, v0);
        float d01 = glm::dot(v0, v1);
        float d11 = glm::dot(v1, v1);
        float d20 = glm::dot(v2, v0);
        float d21 = glm::dot(v2, v1);
        float denom = d00 * d11 - d01 * d01;
        glm::vec3 result;
        result.y = (d11 * d20 - d01 * d21) / denom;
        result.z = (d00 * d21 - d01 * d20) / denom;
        result.x = 1.0f - result.y - result.z;
        return result;
    }
}


