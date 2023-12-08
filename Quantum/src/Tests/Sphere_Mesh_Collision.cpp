#include "QuantumPch.h"
#include "Tests/Sphere_Mesh_Collision.h"
#include <DataStructs/ExtendedTriangle.h>

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSphereMeshCollisionPoints(const SphereCollider3D* colliderA, const glm::mat4& transformA, const MeshCollider3D* colliderB, const glm::mat4& transformB)
	{
        std::vector<CollisionInfo> result;

        glm::mat4 sphereTransform = glm::translate(transformA, colliderA->GetOffset());
        glm::mat4 meshTransform = glm::translate(transformB, colliderB->GetOffset());

        size_t arraySize = colliderB->Colliders.size();
        std::vector<ExtendedTriangle> extendedTriangles(arraySize);

        for (int i = 0; i < arraySize; i++) {
            for (int j = 0; j < 3; j++) 
                extendedTriangles[i].Positions[j] = meshTransform * glm::vec4(colliderB->Colliders[i].Positions[j], 1.f);

            // Calculate the normal of the scaled triangle
            glm::vec3 edge1 = extendedTriangles[i].Positions[1] - extendedTriangles[i].Positions[0];
            glm::vec3 edge2 = extendedTriangles[i].Positions[2] - extendedTriangles[i].Positions[0];
            extendedTriangles[i].Normal = glm::normalize(glm::cross(edge1, edge2));
        }

        // Iterate over every triangle an determine collision
        for (int i = 0; i < arraySize; i++) {
            CollisionInfo info;
            if (FindSphereTriangleCollisionPoints(sphereTransform, colliderA->Radius, extendedTriangles[i], info))
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

    bool SphereTriangleEdgeIntersect(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& v0, const glm::vec3& v1, CollisionInfo& outInfo)
    {
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


