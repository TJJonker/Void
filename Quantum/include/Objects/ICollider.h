#pragma once
#include "Common.h"

namespace Quantum {

	enum class ColliderType {
		Sphere = 0,
		Mesh = 1,
		Box = 2,
		Plane = 3
	};

	class ICollider {
	public:
		ColliderType GetType() { return m_Type; }
	
	protected:
		ICollider(ColliderType colliderType)
			: m_Type(colliderType) { }

		virtual ~ICollider() = default;

	private:
		ColliderType m_Type;
	};
}