#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <glm/glm.hpp>

namespace Void {
	struct CameraComponent {
		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		float FOV = 45.0f;
		float Yaw = -90.0f;
		float Pitch = 0.0f;
	};
}