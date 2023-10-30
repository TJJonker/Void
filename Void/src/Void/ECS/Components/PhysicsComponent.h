#pragma once
#include "glm/glm.hpp"
#include <Void/Physics/Colliders/Collider.h>

namespace Void {
	struct PhysicsComponent {
		float Mass;
		glm::vec3 Velocity;
		glm::vec3 Force;

		bool IsStatic;

		Collider* Collider;
	};
}