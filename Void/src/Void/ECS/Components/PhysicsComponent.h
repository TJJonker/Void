#pragma once
#include "glm/glm.hpp"

namespace Void {
	struct PhysicsComponent {
		float Mass;
		glm::vec3 Velocity;
		glm::vec3 Force;
	};
}