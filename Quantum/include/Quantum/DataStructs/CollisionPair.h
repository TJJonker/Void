#pragma once
#include "Quantum/Objects/ICollider.h"

namespace Quantum {
	struct CollisionPair {
		const ICollider* ColliderA;
		const ICollider* ColliderB;

		bool operator==(const CollisionPair& other) const {
			return (
				(ColliderA == other.ColliderA && ColliderB == other.ColliderB) ||
				(ColliderA == other.ColliderB && ColliderB == other.ColliderA)
				);
		}
	};
}