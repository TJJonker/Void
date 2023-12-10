#pragma once
#include "Quantum/Common.h"
#include "Quantum/Phases/Broad/Core/IBroadPhase.h"
#include "Quantum/DataStructs/CollisionPair.h"
#include <Quantum/DataStructs/AABB.h>
#include <Quantum/DataStructs/OctreeNode.h>

namespace Quantum::BroadPhase {
	typedef std::function<void(const AABB& boundingBox)> DebugCallback;
	
	class Octree : public IBroadPhase
	{
	public:
		Octree(const AABB& worldBounds, uint8_t maxDepth)
			: m_MaxDepth(maxDepth), m_RootNode({}) { }

		virtual void Execute(const std::vector<ICollider*>& colliders, std::vector<CollisionPair>& outColissionInfo) override;
		virtual void VisualiseDebug() override;

		void SetDebugCallback(DebugCallback callback) { m_DebugCallback = callback; }

	private:
		// Checking
		void ExecuteRecursive(OctreeNode& node, std::vector<Quantum::CollisionPair>& outColissionInfo);
		void CheckNodeCollisions(OctreeNode& node, std::vector<Quantum::CollisionPair>& outColissionInfo);
		bool ShouldCheckCollision(const Quantum::ICollider* colliderA, const Quantum::ICollider* colliderB) const;
		bool IsCollisionPairAlreadyPresent(const std::vector<Quantum::CollisionPair>& outColissionInfo, const Quantum::ICollider* smallerCollider, const Quantum::ICollider* largerCollider) const;

		// Inserting
		void InsertRecursive(OctreeNode& node, ICollider* collider, uint8_t depth);
		std::vector<int> GetIntersectingOctants(const AABB& nodeBox, const AABB& objectBox);
		bool IsObjectInBox(const AABB& box, const AABB& objectBox);

		void DebugRecursive(OctreeNode* node);

	private:
		uint8_t m_MaxDepth;
		OctreeNode m_RootNode;
		DebugCallback m_DebugCallback;
	};
}
