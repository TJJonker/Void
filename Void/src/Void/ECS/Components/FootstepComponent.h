#pragma once
#include <glm/glm.hpp>

namespace Void {
	struct FootStepComponent {
		glm::vec3 LastStepPosition = glm::vec3(0);
		float TimeSinceLastStep = 0;
		bool IsLeft = false;
	};
}