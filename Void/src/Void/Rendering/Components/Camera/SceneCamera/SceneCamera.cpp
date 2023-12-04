#include "pch.h"
#include "SceneCamera.h"

namespace Void {
	SceneCamera::SceneCamera()
	{
		CalculateProjection();
	}

	void SceneCamera::SetViewPort(glm::vec2 size)
	{
		m_AspectRatio = (float)size.x / (float)size.y;
		CalculateProjection();
	}

	void SceneCamera::CalculateProjection()
	{
		m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	}
}
