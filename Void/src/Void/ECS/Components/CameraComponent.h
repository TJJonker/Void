#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <glm/glm.hpp>

namespace Void {
	struct CameraComponent {
		glm::vec3 Front;
		glm::vec3 Up;

		float FOV;
		float Yaw;
		float Pitch;
	};
}