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

	std::vector<CollisionInfo> CollisionHandler::RunNarrowPhase(const ICollider* collider1, glm::mat4& transform1, const ICollider* collider2, glm::mat4& transform2)
	{
		m_NarrowPhase->Execute(collider1, transform1, collider2, transform2);
	}
}