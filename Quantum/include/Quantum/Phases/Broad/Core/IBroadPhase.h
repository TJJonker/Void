#pragma once
#include "Quantum/Common.h"
#include "Quantum/DataStructs/CollisionInfo.h"
#include "Quantum/DataStructs/CollisionPair.h"

namespace Quantum {
	class IBroadPhase {
	public:
		virtual ~IBroadPhase() = default;
		virtual void Execute(const std::vector<ICollider*>& colliders, std::vector<CollisionPair>& outColissionInfo) = 0;
		virtual void VisualiseDebug() = 0;
	};
}