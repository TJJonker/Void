#pragma once
#include "ICollider.h"

namespace Quantum {
	class SphereCollider3D : public ICollider {
	public:
		float Radius;
	};
}