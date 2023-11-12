#include "pch.h"
#include "ColissionAlgorithms.h"
#include "Void/Rendering/Libraries/Mesh/MeshLibrary.h"
#include "glm/gtx/norm.hpp"

namespace Void::CollisionAlgorithms {

    std::vector<CollisionPoint> FindSphereSphereColissionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
    {
        CollisionPoint result;

        // Calculate the distance between the centers of the two spheres
        glm::vec3 delta = tb->Position + b->Offset - (ta->Position + a->Offset);
        float distance = glm::length(delta);

        // Check for collision by comparing the distance to the sum of the radii
        if (distance <= (a->Radius + b->Radius)) {
            // Calculate the collision normal and depth
            glm::vec3 collisionNormal = glm::normalize(delta);
            float penetrationDepth = (a->Radius + b->Radius) - distance;

            // Fill in the CollisionPoints struct
            result.CollisionPosition = (ta->Position + a->Offset) + (collisionNormal * a->Radius);
            result.Normal = collisionNormal;
            result.Depth = penetrationDepth;
            result.HasCollision = true;
        }
        else {
            // No collision
            result.HasCollision = false;
        }

        return { result };
    }

    std::vector<CollisionPoint> FindSpherePlaneCollisionPoints(const SphereCollider* a, const Transform* ta, const PlaneCollider* b, const Transform* tb)
    {
        glm::vec3 aPosition = ta->Position + a->Offset;
        glm::vec3 bPosition = tb->Position + b->Offset;
        glm::vec3 delta = aPosition - bPosition;

        CollisionPoint result;

        // Calculate the distance from the sphere center to the plane
        float sphereToPlaneDistance = glm::abs(glm::dot(delta, b->Normal));

        if (sphereToPlaneDistance <= a->Radius) {
            glm::vec3 intersectionPoint = aPosition - sphereToPlaneDistance * b->Normal;

            if (glm::abs(intersectionPoint.x - bPosition.x) <= b->HalfExtents.x &&
                glm::abs(intersectionPoint.y - bPosition.y) <= b->HalfExtents.y) {

                result.CollisionPosition = intersectionPoint;
                result.Normal = glm::normalize(delta);
                result.Depth = glm::abs(sphereToPlaneDistance - a->Radius);
                result.HasCollision = true;
            }
        }

        return { result };
    }

    std::vector<CollisionPoint> FindSphereMeshCollisionPoints(const SphereCollider* a, const Transform* ta, const MeshCollider* b, const Transform* tb)
    {
        std::vector<CollisionPoint> collisionPoints;

        glm::vec3 aPosition = ta->Position + a->Offset;

        Rendering::Mesh* mesh = MeshLibrary::GetInstance()->Get(b->MeshName.c_str());
        
        const Rendering::VertexBuffer* vertexBuffer = mesh->Submeshes[0]->getVertexBuffers()[0].get();
        const Rendering::IndexBuffer* indexBuffer = mesh->Submeshes[0]->GetIndexBuffer().get();

        unsigned int stride = vertexBuffer->GetVertexBufferLayout().GetStride();
        const char* vertices = vertexBuffer->GetData();

        const uint32_t* indices = indexBuffer->GetIndices();
        
        // We assume the first element of the bufferlayout is the vertexPosition
        std::vector<Triangle> triangles;

        for (uint32_t i = 0; i < indexBuffer->GetCount(); i += 3) {
            Triangle triangle;
            for (int j = 0; j < 3; j++) {
                uint32_t index = indices[i + j];
                float x = *(float*)&vertices[(index * stride) + (0 * sizeof(float))];
                float y = *(float*)&vertices[(index * stride) + (1 * sizeof(float))];
                float z = *(float*)&vertices[(index * stride) + (2 * sizeof(float))];
                glm::vec3 vertexPosition = glm::vec3(x, y, z) * tb->Scale + tb->Position;
                triangle.positions[j] = glm::vec3(x, y, z);
            }
            triangles.push_back(triangle);
        }

        for (const Triangle& triangle : triangles) {
            
            glm::vec3 spherePositionMeshSpace = glm::vec3(glm::inverse(tb->GetTransformMatrix()) * glm::vec4(aPosition, 1.0f));

            CollisionPoint collisionPoint = FindSphereTriangleCollisionPoints(spherePositionMeshSpace, a->Radius, triangle);
            if (collisionPoint.HasCollision) {
                collisionPoints.push_back(collisionPoint);
            }
        }

        return collisionPoints;
    }

    CollisionPoint FindSphereTriangleCollisionPoints(const glm::vec3 SpherePositionInMeshSpace, const float radius, const Triangle& triangle) {
        CollisionPoint result;

        glm::vec3 v0 = triangle.positions[0];
        glm::vec3 v1 = triangle.positions[1];
        glm::vec3 v2 = triangle.positions[2];

        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        // Project the sphere center onto the plane of the triangle
        float d = glm::dot(normal, v0);
        float distance = glm::dot(normal, SpherePositionInMeshSpace) - d;
            

        if (glm::abs(distance) > radius) {
            result.HasCollision = false;
            return result;
        }

        // Calculate the point on the triangle closest to the sphere center
        glm::vec3 closestPoint = SpherePositionInMeshSpace - distance * normal;

        // Check if the closest point is inside the triangle
        result = PointInTriangle(closestPoint, triangle);
        if (result.HasCollision)
            return result;


        // Check if the sphere intersects with any triangle edge
        result = SphereTriangleEdgeIntersect(SpherePositionInMeshSpace, radius, v0, v1);
        if (result.HasCollision)
            return result;

        result = SphereTriangleEdgeIntersect(SpherePositionInMeshSpace, radius, v1, v2);
        if (result.HasCollision)
            return result;

        result = SphereTriangleEdgeIntersect(SpherePositionInMeshSpace, radius, v2, v0);
        if (result.HasCollision)
            return result;

        return { };
    }

    CollisionPoint PointInTriangle(const glm::vec3& point, const Triangle& triangle)
    {
        CollisionPoint result;

        glm::vec3 v0 = triangle.positions[0];
        glm::vec3 v1 = triangle.positions[1];
        glm::vec3 v2 = triangle.positions[2];

        // Check if the point is inside the triangle using barycentric coordinates
        float d00 = glm::dot(v1 - v0, v1 - v0);
        float d01 = glm::dot(v1 - v0, v2 - v0);
        float d11 = glm::dot(v2 - v0, v2 - v0);
        float d20 = glm::dot(point - v0, v2 - v0);
        float d21 = glm::dot(point - v0, v2 - v1);

        float invDenom = 1.0f / (d00 * d11 - d01 * d01);
        float u = (d11 * d20 - d01 * d21) * invDenom;
        float v = (d00 * d21 - d01 * d20) * invDenom;

        // Check if the barycentric coordinates are within the valid range for a point inside the triangle
        result.HasCollision = (u >= 0.0f) && (v >= 0.0f) && (u + v <= 1.0f);

        if (result.HasCollision) {
            // Calculate the collision position using barycentric coordinates
            result.CollisionPosition = v0 + u * (v1 - v0) + v * (v2 - v0);

            // Calculate the normal vector of the triangle
            result.Normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

            // Calculate the depth of penetration (distance from the point to the triangle)
            result.Depth = glm::length(point - result.CollisionPosition);
        }

        return result;
    }

    CollisionPoint SphereTriangleEdgeIntersect(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& v0, const glm::vec3& v1)
    {
        CollisionPoint result;

        // Calculate the closest point on the edge to the sphere center
        glm::vec3 edgeDirection = glm::normalize(v1 - v0);
        glm::vec3 edgeToPoint = sphereCenter - v0;
        float t = glm::dot(edgeToPoint, edgeDirection);
        glm::vec3 closestPoint;

        if (t < 0.0f)
            closestPoint = v0;
        else if (t > glm::length(v1 - v0))
            closestPoint = v1;
        else
            closestPoint = v0 + t * edgeDirection;

        // Check if the closest point is within the sphere
        bool hasCollision = glm::length2(sphereCenter - closestPoint) <= (sphereRadius * sphereRadius);

        // Fill in the CollisionPoint struct
        result.HasCollision = hasCollision;
        result.CollisionPosition = closestPoint;
        result.Normal = glm::normalize(sphereCenter - closestPoint);
        result.Depth = hasCollision ? (sphereRadius - glm::length(sphereCenter - closestPoint)) : 0.0f;

        return result;
    }
}