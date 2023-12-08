#pragma once
#include "ICollisionTest.h"
#include "DataStructs/Triangle.h"

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSphereMeshCollisionPoints(const SphereCollider3D* colliderA, const glm::mat4& transformA, const MeshCollider3D* colliderB, const glm::mat4& transformB);

	bool FindSphereTriangleCollisionPoints(const glm::mat4& sphereTransform, const float sphereRadius, const ExtendedTriangle& triangle, CollisionInfo& outInfo);
	bool PointInTriangle(const glm::vec3& point, const Triangle& triangle, CollisionInfo& outInfo);
	bool SphereTriangleEdgeIntersect(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& v0, const glm::vec3& v1, CollisionInfo& outInfo);
	glm::vec3 Barycentric(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
}