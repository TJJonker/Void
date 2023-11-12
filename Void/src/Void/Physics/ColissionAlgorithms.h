#pragma once
#include "Void/Physics/CollisionPoints.h"
#include <Void/Physics/Colliders/SphereCollider.h>
#include <Void/Physics/Colliders/PlaneCollider.h>
#include <Void/Physics/Colliders/MeshCollider.h>

namespace Void {
	namespace CollisionAlgorithms {
		std::vector<CollisionPoint> FindSphereSphereColissionPoints(const SphereCollider* a, const Transform* ta,const SphereCollider* b, const Transform* tb);
		std::vector<CollisionPoint> FindSpherePlaneCollisionPoints(const SphereCollider* a, const Transform* ta, const PlaneCollider* b,	 const Transform* tb);
		std::vector<CollisionPoint> FindSphereMeshCollisionPoints(const SphereCollider* a, const Transform* ta, const MeshCollider* b, const Transform* tb);

		// Helper functions
		struct Triangle {
			glm::vec3 positions[3];
		};

		CollisionPoint FindSphereTriangleCollisionPoints(const glm::vec3 SpherePositionInMeshSpace, const float radius, const Triangle& triangle);
		CollisionPoint PointInTriangle(const glm::vec3& point, const Triangle& triangle);
		CollisionPoint SphereTriangleEdgeIntersect(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& v0, const glm::vec3& v1);
	}
}

