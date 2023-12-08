#pragma once

namespace Quantum {
	struct CollisionInfo {
		glm::vec3 CollisionPosition = glm::vec3(0);
		glm::vec3 Normal = glm::vec3(0);
		float Depth;
	};
}