#pragma once
#include "Common.h"
#include <Phases/Broad/Core/IBroadPhase.h>
#include <Phases/Narrow/Core/INarrowPhase.h>
#include <Objects/ICollider.h>
#include "Tests/ICollisionTest.h"

namespace Quantum {
	class CollisionHandler {
	public:
		CollisionHandler(IBroadPhase* broadPhase, INarrowPhase* narrowPhase);
		~CollisionHandler();

		bool TestCollision(const ICollider* collider1, const glm::mat4& transfom1, const ICollider* collider2, const glm::mat4& transform2);

	private:
		IBroadPhase* m_BroadPhase;
		INarrowPhase* m_NarrowPhase;

		ColliderTest colliderTests[4][4] = {
			{ nullptr, nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr, nullptr }
		};
	};
}