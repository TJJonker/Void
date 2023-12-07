#pragma once

namespace Quantum {
	struct CollisionPair {
		const ICollider* Collider1;
		glm::mat4& Transform1;
		const ICollider* Collider2;
		glm::mat4& Transform2;
	};
}