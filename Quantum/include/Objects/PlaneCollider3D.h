#pragma once
#include "ICollider.h"

namespace Quantum {
	class PlaneCollider3D : public ICollider {
	public:
		glm::vec3 Normal;
		glm::vec3 HalfExtents;
	};
}