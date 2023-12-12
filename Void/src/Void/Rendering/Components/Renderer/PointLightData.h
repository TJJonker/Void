#pragma once
#include <glm/glm.hpp>

namespace Void {
	struct PointLightData {
		glm::vec3 Position = glm::vec3(0);
		float Constant = 1.0f;
		float Linear = 0.09f;
		float Quadratic = 0.032f;
		glm::vec3 Ambient = glm::vec3(1.0, 1.0, 1.0);
		glm::vec3 Diffuse = glm::vec3(1.0, 1.0, 1.0);
	};
}