#pragma once
#include "Common.h"
#include <Phases/Broad/Core/IBroadPhase.h>
#include <Phases/Narrow/Core/INarrowPhase.h>
#include <Objects/ICollider.h>

#include "Tests/Sphere_Sphere_Collision.h"
#include "Tests/Sphere_Plane_Collision.h"
#include "Tests/Sphere_Mesh_Collision.h"

namespace Quantum {
	class CollisionHandler {
	public:
		CollisionHandler(IBroadPhase* broadPhase, INarrowPhase* narrowPhase);
		~CollisionHandler();

		//std::vector<CollisionPair> RunBroadPhase();
		std::vector<CollisionInfo> RunNarrowPhase(const ICollider* collider1, glm::mat4& transfom1, const ICollider* collider2, glm::mat4& transform2);

	private:
		IBroadPhase* m_BroadPhase;
		INarrowPhase* m_NarrowPhase;
	};
}