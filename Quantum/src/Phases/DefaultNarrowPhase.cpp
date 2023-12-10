#include "Quantum/QuantumPch.h"
#include "Quantum/Phases/Narrow/DefaultNarrowPhase.h"

namespace Quantum::NarrowPhase {

    std::vector<CollisionInfo> DefaultNarrowPhase::Execute(const ICollider* collider1, glm::mat4& transform1, const ICollider* collider2, glm::mat4& transform2)
    {
		if (collider1->GetType() > collider2->GetType()) {
			const ICollider* tempCollider = collider1;
			collider1 = collider2;
			collider2 = tempCollider;

			const glm::mat4* tempTransform = &transform1;
			transform1 = transform2;
			transform2 = *tempTransform;
		}

		return colliderTests[(int)collider1->GetType()][(int)collider2->GetType()](collider1, transform1, collider2, transform2);
    }
}
