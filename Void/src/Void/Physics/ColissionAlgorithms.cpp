#include "pch.h"
#include "ColissionAlgorithms.h"
#include "Void/Rendering/Libraries/Mesh/MeshLibrary.h"
#include "glm/gtx/norm.hpp"

namespace Void::CollisionAlgorithms {

    std::vector<CollisionPoint> FindSphereSphereColissionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
    {
        CollisionPoint result;

        // Calculate the distance between the centers of the two spheres
        glm::vec3 delta = tb->Position - ta->Position;
        float distance = glm::length(delta);

        // Check for collision by comparing the distance to the sum of the radii
        if (distance < (a->Radius + b->Radius)) {
            // Calculate the collision normal and depth
            glm::vec3 collisionNormal = glm::normalize(delta);
            float penetrationDepth = (a->Radius + b->Radius) - distance;

            // Fill in the CollisionPoints struct
            result.CollisionPosition = (ta->Position + a->Offset) + (collisionNormal * a->Radius);
            result.Normal = -collisionNormal;
            result.Depth = penetrationDepth;
            result.HasCollision = true;

            VOID_CORE_WARN("Sphere Collision");
            VOID_CORE_TRACE("APosition: {0}, {1}, {2}", ta->Position.x, ta->Position.y, ta->Position.z);
            VOID_CORE_TRACE("BPosition: {0}, {1}, {2}", tb->Position.x, tb->Position.y, tb->Position.z);
            VOID_CORE_TRACE("Distance betweem: {0}", distance);
            VOID_CORE_TRACE("Normal {0}, {1}, {2}", -collisionNormal.x, -collisionNormal.y, -collisionNormal.z);
            VOID_CORE_TRACE("Penetration depth: {0}", penetrationDepth);
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

        glm::vec3 sphereCenterWorldSpace = ta->Position + a->Offset;

        // Retrieve mesh data.
        Rendering::Mesh* mesh = MeshLibrary::GetInstance()->Get(b->MeshName.c_str());
        const Rendering::VertexBuffer* vertexBuffer = mesh->Submeshes[0]->getVertexBuffers()[0].get();
        const Rendering::IndexBuffer* indexBuffer = mesh->Submeshes[0]->GetIndexBuffer().get();
        unsigned int stride = vertexBuffer->GetVertexBufferLayout().GetStride();
        const char* vertices = vertexBuffer->GetData();
        const uint32_t* indices = indexBuffer->GetIndices();

        // Create triangles
        // We assume the first element of the buffer layout is the vertex position
        std::vector<Triangle> triangles;
        for (uint32_t i = 0; i < indexBuffer->GetCount(); i += 3) {
            Triangle triangle;
            for (int j = 0; j < 3; j++) {
                uint32_t index = indices[i + j];
                float x = *(float*)&vertices[(index * stride) + (0 * sizeof(float))];
                float y = *(float*)&vertices[(index * stride) + (1 * sizeof(float))];
                float z = *(float*)&vertices[(index * stride) + (2 * sizeof(float))];

                glm::vec4 local_position(x, y, z, 1.0f);
                glm::mat4 tm = tb->GetTransformMatrix();
                glm::vec4 world_position = tm * local_position;
                triangle.Positions[j] = glm::vec3(world_position);
            }

            // Calculate the normal of the scaled triangle
            glm::vec3 edge1 = triangle.Positions[1] - triangle.Positions[0];
            glm::vec3 edge2 = triangle.Positions[2] - triangle.Positions[0];
            triangle.Normal = glm::normalize(glm::cross(edge1, edge2));

            triangles.push_back(triangle);
        }

        // Iterate over every triangle an determine collision
        for (const Triangle& triangle : triangles) {
            CollisionPoint collisionPoint = FindSphereTriangleCollisionPoints(sphereCenterWorldSpace, a->Radius, triangle);
            if (collisionPoint.HasCollision) {
                collisionPoints.push_back(collisionPoint);
            }
        }

        return collisionPoints;
    }

    CollisionPoint FindSphereTriangleCollisionPoints(const glm::vec3 sphereWorldSpacePosition, const float sphereRadius, const Triangle& triangleWorldSpace)
    {
        CollisionPoint result;

        glm::vec3 v0 = triangleWorldSpace.Positions[0];
        glm::vec3 v1 = triangleWorldSpace.Positions[1];
        glm::vec3 v2 = triangleWorldSpace.Positions[2];

        // Project the sphere center onto the plane of the triangle
        float d = glm::dot(triangleWorldSpace.Normal, v0);
        float distance = glm::dot(triangleWorldSpace.Normal, sphereWorldSpacePosition) - d;

        if (glm::abs(distance) > sphereRadius) {
            result.HasCollision = false;
            return result;
        }

         // Calculate the point on the triangle closest to the sphere center
         glm::vec3 closestPoint = sphereWorldSpacePosition - distance * triangleWorldSpace.Normal;

         // Check if the closest point is inside the triangle
         result = PointInTriangle(closestPoint, triangleWorldSpace);
         if (result.HasCollision) {
             result.Depth = sphereRadius - distance;
             return result;
         }

         // Check if the sphere intersects with any triangle edge
         result = SphereTriangleEdgeIntersect(sphereWorldSpacePosition, sphereRadius, v0, v1);
         if (result.HasCollision)
             return result;

         result = SphereTriangleEdgeIntersect(sphereWorldSpacePosition, sphereRadius, v1, v2);
         if (result.HasCollision)
             return result;

         result = SphereTriangleEdgeIntersect(sphereWorldSpacePosition, sphereRadius, v2, v0);
         if (result.HasCollision)
             return result;

            return {};
    }

    CollisionPoint PointInTriangle(const glm::vec3& pointWorldSpace, const Triangle& triangleWorldSpace)
    {
        CollisionPoint result;

        glm::vec3 v0 = triangleWorldSpace.Positions[0];
        glm::vec3 v1 = triangleWorldSpace.Positions[1];
        glm::vec3 v2 = triangleWorldSpace.Positions[2];

        glm::vec3 barycentric = Barycentric(pointWorldSpace, v0, v1, v2);

        // Check if the barycentric coordinates are within the valid range for a point inside the triangle
        result.HasCollision = (barycentric.x >= 0.0f && barycentric.y >= 0.0f && barycentric.z >= 0.0f &&
            barycentric.x <= 1.0f && barycentric.y <= 1.0f && barycentric.z <= 1.0f);

        if (result.HasCollision) {
            // Calculate the collision position using barycentric coordinates
            result.CollisionPosition = barycentric.x * v0 + barycentric.y * v1 + barycentric.z * v2;

            // Calculate the normal vector of the triangle
            result.Normal = triangleWorldSpace.Normal;
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