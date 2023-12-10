#pragma once
#include "ICollisionTest.h"
#include "Quantum/DataStructs/ExtendedTriangle.h"

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSphereMeshCollisionPoints(const ICollider* colliderA, const glm::mat4& transformA, const ICollider* colliderB, const glm::mat4& transformB);

	bool FindSphereTriangleCollisionPoints(const glm::mat4& sphereTransform, const float sphereRadius, const ExtendedTriangle& triangle, CollisionInfo& outInfo);
	bool PointInTriangle(const glm::vec3& point, const ExtendedTriangle& triangle, CollisionInfo& outInfo);
	bool SphereTriangleEdgeIntersect(const glm::vec3& spherePosition, const float sphereRadius, const glm::vec3& v0, const glm::vec3& v1, CollisionInfo& outInfo);
	glm::vec3 Barycentric(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
}