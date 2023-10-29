#pragma once
#include "glm/glm.hpp"

namespace Void {
	struct TransformComponent {
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
	};
}