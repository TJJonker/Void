#pragma once
#include "Quantum/Common.h"
#include "Quantum/DataStructs/CollisionInfo.h"
#include "Quantum/DataStructs/CollisionPair.h"

#include "Quantum/Objects/SphereCollider3D.h"
#include "Quantum/Objects/MeshCollider3D.h"
#include "Quantum/Objects/BoxCollider3D.h"
#include "Quantum/Objects/PlaneCollider3D.h"

namespace Quantum::Tests {
	using ColliderTest = std::vector<CollisionInfo>(*)(const ICollider* colliderA, const glm::mat4& transformA, const ICollider* colliderB, const glm::mat4& transformB);
}