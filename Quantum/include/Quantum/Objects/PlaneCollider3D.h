#pragma once
#include "ICollider.h"

namespace Quantum {
	class PlaneCollider3D : public ICollider {
	public:
		PlaneCollider3D(uint32_t id) 
			:ICollider(ColliderType::Plane) { }

	public:
		glm::vec3 Normal;
		glm::vec3 HalfExtents;
	};
}