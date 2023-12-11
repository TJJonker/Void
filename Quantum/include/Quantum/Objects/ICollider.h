#pragma once
#include "Quantum/DataStructs/AABB.h"

namespace Quantum {
	static uint32_t ID = 0;

	enum class ColliderType {
		Sphere = 0,
		Mesh = 1,
		Box = 2,
		Plane = 3
	};

	class ICollider {
	public:
		ColliderType GetType() const { return m_Type; }

		glm::vec3 GetOffset() const { return m_Offset; }
		void SetOffset(const glm::vec3& offset) { m_Offset = offset; }

		bool IsTrigger() const { return m_Trigger; }
		void SetTrigger(bool isTrigger) { m_Trigger = isTrigger; }

		bool IsStatic() const { return m_Static; }
		void SetStatic(bool isStatic) { m_Static = isStatic; }

		AABB GetBoundingBox() const { return m_BoundingBox; }
		virtual void CalculateBoundingBox(const glm::mat4& transform) = 0;

		uint32_t GetID() const { return m_ID; }
		void SetID(uint32_t id) { m_ID = id; }

	protected:
		ICollider(ColliderType colliderType)
			: m_Type(colliderType), m_Offset({ 0 }), m_Trigger(false), m_ID(ID++), m_Static(false) { }

		virtual ~ICollider() = default;

	protected:
		AABB m_BoundingBox;

	private:
		uint32_t m_ID;
		ColliderType m_Type;

		glm::vec3 m_Offset;
		bool m_Trigger;
		bool m_Static;
	};
}