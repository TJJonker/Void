#pragma once
#include "Common.h"
#include "Tests/Tests.h"
#include "Phases/Narrow/Core/INarrowPhase.h"

namespace Quantum::NarrowPhase {
	class DefaultNarrowPhase : public INarrowPhase
	{
	public:
		virtual std::vector<CollisionInfo> Execute(const ICollider* collider1, glm::mat4& transform1, const ICollider* collider2, glm::mat4& transform2) override;

	private:
		//			Sphere   Plane	 Box	Mesh
		// Sphere
		// Plane
		// Box
		// Mesh

		Tests::ColliderTest colliderTests[4][4] = {
			{ Tests::FindSphereSphereColissionPoints,	Tests::FindSpherePlaneCollisionPoints,	nullptr, Tests::FindSphereMeshCollisionPoints },
			{ nullptr,									nullptr,								nullptr, nullptr },
			{ nullptr,									nullptr,								nullptr, nullptr },
			{ nullptr,									nullptr,								nullptr, nullptr }
		};


	};
}
