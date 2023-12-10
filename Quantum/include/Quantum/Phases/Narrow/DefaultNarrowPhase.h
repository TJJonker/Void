#pragma once
#include "Quantum/Common.h"
#include "Quantum/Tests/Tests.h"
#include "Quantum/Phases/Narrow/Core/INarrowPhase.h"

namespace Quantum::NarrowPhase {
	class DefaultNarrowPhase : public INarrowPhase
	{
	public:
		virtual std::vector<CollisionInfo> Execute(const ICollider* collider1, glm::mat4& transform1, const ICollider* collider2, glm::mat4& transform2) override;

	private:
		//			Sphere   Mesh	 Box	Plane
		// Sphere
		// Mesh
		// Box
		// Plane

		Tests::ColliderTest colliderTests[4][4] = {
			{ Tests::FindSphereSphereColissionPoints,	Tests::FindSphereMeshCollisionPoints,	nullptr, Tests::FindSpherePlaneCollisionPoints },
			{ nullptr,									nullptr,								nullptr, nullptr },
			{ nullptr,									nullptr,								nullptr, nullptr },
			{ nullptr,									nullptr,								nullptr, nullptr }
		};


	}; 
}
