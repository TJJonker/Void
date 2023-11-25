#pragma once
#include "fmod/fmod.hpp"
#include "glm/glm.hpp"

namespace Void::Audio {
	FMOD_VECTOR ToFMOD(glm::vec3 vec) {
		return { vec.x, vec.y, vec.z };
	}
}