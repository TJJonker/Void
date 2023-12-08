#pragma once
#include "ICollisionTest.h"

namespace Quantum::Tests {
	std::vector<CollisionInfo> FindSpherePlaneCollisionPoints(const SphereCollider3D* colliderA, const glm::mat4& transfomA, const PlaneCollider3D* colliderB, const glm::mat4& transformB);
}