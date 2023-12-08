#pragma once
#include "Common.h"
#include "DataStructs/CollisionInfo.h"
#include "DataStructs/CollisionPair.h"

#include "Objects/SphereCollider3D.h"
#include "Objects/MeshCollider3D.h"
#include "Objects/BoxCollider3D.h"
#include "Objects/PlaneCollider3D.h"

namespace Quantum::Tests {
	typedef std::function<std::vector<CollisionInfo>(const ICollider* colliderA, const glm::mat4& transformA, const ICollider* colliderB, const glm::mat4& transformB)> ColliderTest;
}