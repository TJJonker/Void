#include "Quantum/QuantumPch.h"
#include "Quantum/CollisionHandler.h"

namespace Quantum {
	CollisionHandler::CollisionHandler(IBroadPhase* broadPhase, INarrowPhase* narrowPhase)
		: m_BroadPhase(broadPhase), m_NarrowPhase(narrowPhase) { }

	CollisionHandler::~CollisionHandler()
	{
		delete m_BroadPhase;
		delete m_NarrowPhase;
	}

	void CollisionHandler::RunBroadPhase(const std::vector<ICollider*>& colliders, std::vector<CollisionPair>& outColissionInfo)
	{
		m_BroadPhase->Execute(colliders, outColissionInfo);
	}

	std::vector<CollisionInfo> CollisionHandler::RunNarrowPhase(const ICollider* collider1, glm::mat4& transform1, const ICollider* collider2, glm::mat4& transform2)
	{
		return m_NarrowPhase->Execute(collider1, transform1, collider2, transform2);
	}

	void CollisionHandler::DebugBroadPhase() 
	{
		m_BroadPhase->VisualiseDebug();
	}
}