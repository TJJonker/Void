#pragma once
#include <vector>

namespace Void::Physics {
	class IBroadPhase {
	public:
		virtual ~IBroadPhase() = default;
		virtual void GetColissionPairs(const std::vector<Entity*> entities)
	};
}