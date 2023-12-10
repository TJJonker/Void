#include "Quantum/QuantumPch.h"
#include "Quantum/Objects/BoxCollider3D.h"

namespace Quantum {
	void BoxCollider3D::CalculateBoundingBox(const glm::mat4& transform)
	{
        // Transform the local space bounding box to world space
        glm::vec3 minWorld = glm::vec3(transform * glm::vec4(-HalfExtents, 1.0f));
        glm::vec3 maxWorld = glm::vec3(transform * glm::vec4(HalfExtents, 1.0f));

        // Assign the calculated AABB to the collider
        m_BoundingBox.Min = minWorld;
        m_BoundingBox.Max = maxWorld;
	}
}