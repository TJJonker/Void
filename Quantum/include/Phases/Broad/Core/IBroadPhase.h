#pragma once
#include "Common.h"
#include "DataStructs/CollisionInfo.h"

namespace Quantum {
	class IBroadPhase {
	public:
		virtual ~IBroadPhase() = default;
		virtual void FindColissions(std::vector<CollisionInfo>& outColissionInfo) = 0;
		virtual void VisualiseDebug() = 0;
	};
}