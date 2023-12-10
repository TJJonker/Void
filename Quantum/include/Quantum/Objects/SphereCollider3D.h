#pragma once
#include "ICollider.h"

namespace Quantum {
	class SphereCollider3D : public ICollider {
	public:
		SphereCollider3D(uint32_t id) 
			: ICollider(ColliderType::Sphere) { }
	
	public:
		float Radius;
	};
}