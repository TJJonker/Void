#pragma once
#include "ICollisionTest.h"

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSpherePlaneCollisionPoints(const ICollider* colliderA, const glm::mat4& transfomA, const ICollider* colliderB, const glm::mat4& transformB);
}