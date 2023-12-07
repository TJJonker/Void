#include "QuantumPch.h"
#include "CollisionHandler.h"

namespace Quantum {
	CollisionHandler::CollisionHandler(IBroadPhase* broadPhase, INarrowPhase* narrowPhase)
		: m_BroadPhase(broadPhase), m_NarrowPhase(narrowPhase) { }

	CollisionHandler::~CollisionHandler()
	{
		delete m_BroadPhase;
		delete m_NarrowPhase;
	}

	bool CollisionHandler::TestCollision(const ICollider* collider1, const glm::mat4& transfom1, const ICollider* collider2, const glm::mat4& transform2)
	{
		return false;
	}
}