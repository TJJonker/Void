#pragma once
#include "ICollider.h"
#include <Quantum/DataStructs/Triangle.h>

namespace Quantum {
	class MeshCollider3D : public ICollider {
	public:
		MeshCollider3D(uint32_t id) 
			: ICollider(ColliderType::Mesh) { }

	public:
		std::vector<Triangle> Colliders;
	};
}