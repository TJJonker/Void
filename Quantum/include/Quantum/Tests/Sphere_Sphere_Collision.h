#pragma once
#include "ICollisionTest.h"

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSphereSphereColissionPoints(const ICollider* colliderA, const glm::mat4& transformA, const ICollider* colliderB, const glm::mat4& transformB);
}