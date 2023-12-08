#pragma once
#include "ICollisionTest.h"

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSphereSphereColissionPoints(const SphereCollider3D* colliderA, const glm::mat4& transformA, const SphereCollider3D* colliderB, const glm::mat4& transformB);
}