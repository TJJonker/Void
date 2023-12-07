#pragma once
#include "Common.h"
#include "DataStructs/CollisionInfo.h"
#include "DataStructs/CollisionPair.h"
#include <Objects/ICollider.h>

namespace Quantum {
	typedef std::function<std::vector<CollisionInfo>(const CollisionPair&)> ColliderTest;
}