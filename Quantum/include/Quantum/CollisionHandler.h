#pragma once
#include "Quantum/Common.h"
#include <Quantum/Phases/Broad/Core/IBroadPhase.h>
#include <Quantum/Phases/Narrow/Core/INarrowPhase.h>
#include <Quantum/Objects/ICollider.h>

namespace Quantum {
	class CollisionHandler {
	public:
		CollisionHandler(IBroadPhase* broadPhase, INarrowPhase* narrowPhase);
		~CollisionHandler();

		void RunBroadPhase(const std::vector<ICollider*>& colliders, std::vector<CollisionPair>& outColissionInfo);
		std::vector<CollisionInfo> RunNarrowPhase(const ICollider* collider1, glm::mat4& transfom1, const ICollider* collider2, glm::mat4& transform2);

		void DebugBroadPhase();

	private:
		IBroadPhase* m_BroadPhase;
		INarrowPhase* m_NarrowPhase;
	};
}