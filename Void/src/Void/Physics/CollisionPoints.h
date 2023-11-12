#pragma once
#include <glm/glm.hpp>

namespace Void {
	struct CollisionPoint {
		glm::vec3 CollisionPosition;
		glm::vec3 Normal;
		float Depth;
		bool HasCollision = false;
	};
}