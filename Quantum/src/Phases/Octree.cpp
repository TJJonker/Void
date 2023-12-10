#include "Quantum/QuantumPch.h"
#include "Quantum/Phases/Broad/Octree/Octree.h"

namespace Quantum::BroadPhase {

	void Octree::Execute(const std::vector<ICollider*>& colliders, std::vector<CollisionPair>& outColissionInfo)
	{
		for(ICollider* collider : colliders)
			InsertRecursive(m_RootNode, collider, m_MaxDepth);\
		ExecuteRecursive(m_RootNode, outColissionInfo);
	}

	void Octree::VisualiseDebug()
	{
		DebugRecursive(m_RootNode);
	}

#pragma region Debug
	void Octree::DebugRecursive(OctreeNode& node)
	{
		m_DebugCallback(node.BoundingBox);
		for (int i = 0; i < 8; i++) {
			if (node.SubNodes[i] != nullptr) {
				DebugRecursive(node.SubNodes[i]);
			}
		}
	}
#pragma endregion


#pragma region Checking
	void Octree::ExecuteRecursive(OctreeNode& node, std::vector<Quantum::CollisionPair>& outColissionInfo)
	{
		CheckNodeCollisions(node, outColissionInfo);

		for (int i = 0; i < 8; ++i) {
			if (node.SubNodes[i] != nullptr) {
				ExecuteRecursive(node->SubNodes[i], outColissionInfo);
			}
		}
	}

	void Octree::CheckNodeCollisions(OctreeNode* node, std::vector<Quantum::CollisionPair>& outColissionInfo)
	{
		const std::vector<Quantum::ICollider*>& colliders = node->Objects;
		const size_t numColliders = colliders.size();

		// Check collisions between colliders in the same node
		for (size_t i = 0; i < numColliders; ++i) {
			for (size_t j = i + 1; j < numColliders; ++j) {
				// Broad phase collision check
				if (ShouldCheckCollision(colliders[i], colliders[j])) {
					// Ensure consistent order of colliders in the pair
					Quantum::ICollider* smallerCollider = std::min(colliders[i], colliders[j]);
					Quantum::ICollider* largerCollider = std::max(colliders[i], colliders[j]);

					// Check if the collision pair is already in the output vector
					if (!IsCollisionPairAlreadyPresent(outColissionInfo, smallerCollider, largerCollider)) {
						// Add the potential collision pair to the output vector
						outColissionInfo.push_back({ smallerCollider, largerCollider });
					}
				}
			}
		}
	}

	bool Octree::ShouldCheckCollision(const Quantum::ICollider* colliderA, const Quantum::ICollider* colliderB) const {
		// For simplicity, let's assume all pairs should be checked in this example
		return true;
	}

	bool Octree::IsCollisionPairAlreadyPresent(const std::vector<Quantum::CollisionPair>& outColissionInfo, const Quantum::ICollider* smallerCollider, const Quantum::ICollider* largerCollider) const
	{
		return std::find(outColissionInfo.begin(), outColissionInfo.end(),
			Quantum::CollisionPair{ smallerCollider, largerCollider }) != outColissionInfo.end();
	}
#pragma region

#pragma region Inserting
	void Octree::InsertRecursive(OctreeNode* node, ICollider* collider, uint8_t depth)
	{
		// Check if lasts and overlaps

		if (depth == 0 && IsObjectInBox(node->BoundingBox, collider->GetBoundingBox())) {
			// If the object spans multiple octants or we reached the maximum depth, insert in current node
			node->Objects.push_back(collider);
			return;
		}

		// Determine which octants the object intersects
		std::vector<int> intersectingOctants = GetIntersectingOctants(node->BoundingBox, collider->GetBoundingBox());

		for (int octant : intersectingOctants) {
			// Create the child node if it doesn't exist
			if (node->SubNodes[octant] == nullptr) {
				// Subdivide the bounding box into octants
				glm::vec3 min = node->BoundingBox.Min;
				glm::vec3 max = node->BoundingBox.Max;
				glm::vec3 mid = 0.5f * (min + max);

				// Create bounding box for the octant
				AABB octantBox;
				octantBox.Min = glm::vec3(octant & 1 ? mid.x : min.x,
					octant & 2 ? mid.y : min.y,
					octant & 4 ? mid.z : min.z);
				octantBox.Max = glm::vec3(octant & 1 ? max.x : mid.x,
					octant & 2 ? max.y : mid.y,
					octant & 4 ? max.z : mid.z);

				// Create the child node
				node->SubNodes[octant] = new OctreeNode(octantBox);
			}

			// Recursively insert the object into the appropriate octant
			InsertRecursive(node->SubNodes[octant], collider, depth - 1);
		}
	}

	std::vector<int> Octree::GetIntersectingOctants(const AABB& nodeBox, const AABB& objectBox)
	{
		std::vector<int> intersectingOctants;

		glm::vec3 mid = 0.5f * (nodeBox.Min + nodeBox.Max);

		for (int octant = 0; octant < 8; ++octant) {
			AABB octantBox;
			octantBox.Min = glm::vec3(octant & 1 ? mid.x : nodeBox.Min.x,
				octant & 2 ? mid.y : nodeBox.Min.y,
				octant & 4 ? mid.z : nodeBox.Min.z);
			octantBox.Max = glm::vec3(octant & 1 ? nodeBox.Max.x : mid.x,
				octant & 2 ? nodeBox.Max.y : mid.y,
				octant & 4 ? nodeBox.Max.z : mid.z);

			if (IsObjectInBox(octantBox, objectBox)) {
				intersectingOctants.push_back(octant);
			}
		}

		return intersectingOctants;
	}

	bool Octree::IsObjectInBox(const AABB & box, const AABB & objectBox)
	{
		return (box.Min.x <= objectBox.Max.x && box.Max.x >= objectBox.Min.x) &&
			(box.Min.y <= objectBox.Max.y && box.Max.y >= objectBox.Min.y) &&
			(box.Min.z <= objectBox.Max.z && box.Max.z >= objectBox.Min.z);
	}

#pragma endregion
}