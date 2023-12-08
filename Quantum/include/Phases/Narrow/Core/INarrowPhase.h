#pragma once

namespace Quantum {
	class INarrowPhase {
	public:
		virtual ~INarrowPhase() = default;
		virtual std::vector<CollisionInfo> Execute(const ICollider* collider1, glm::mat4& transform1, const ICollider* collider2, glm::mat4& transform2) = 0;
	};
}