#pragma once
#include "ICollider.h"
#include <DataStructs/Triangle.h>

namespace Quantum {
	class MeshCollider3D : public ICollider {
	public:
		std::vector<Triangle> Colliders;
	};
}