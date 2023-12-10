#pragma once
#include "Quantum/Objects/ICollider.h"

namespace Quantum {
	class BoxCollider3D : public ICollider {
	public:
		BoxCollider3D() 
			: ICollider(ColliderType::Box) {}

	public:
		glm::vec3 HalfExtents;

		// Inherited via ICollider
		virtual void CalculateBoundingBox(const glm::mat4& transform) override;
	};
}
