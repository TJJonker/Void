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
		
		glm::vec3 GetOffset() const { return m_Offset; }
		void SetOffset(const glm::vec3& offset) { m_Offset = offset; }

		bool IsTrigger() const { return m_Trigger; }
		void SetTrigger(bool isTrigger) { m_Trigger = isTrigger; }

		ColliderType GetType() const { return m_Type; }

	protected:
		ICollider(ColliderType colliderType, uint32_t id)
			: m_Type(colliderType), m_Offset({0}), m_Trigger(false) { }

		virtual ~ICollider() = default;

	private:
		ColliderType m_Type;
		glm::vec3 m_Offset;
		bool m_Trigger;
	};
}