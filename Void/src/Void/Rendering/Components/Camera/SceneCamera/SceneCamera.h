#pragma once
#include "Void/Rendering/Components/Camera/Core/Camera.h"

namespace Void {
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		~SceneCamera() = default;

		void SetViewPort(glm::vec2 size);

		void SetFOV(float fov) { m_FOV = fov; CalculateProjection(); }
		void SetNearClip(float nearClip) { m_NearClip = nearClip; CalculateProjection(); }
		void SetFarClip(float farClip) { m_FarClip = farClip; CalculateProjection(); }

		float GetFOV() const { return m_FOV; }
		float GetNearClip() const { return m_NearClip; }
		float GetFarClip() const { return m_FarClip; }

	private:
		void CalculateProjection();

	private:
		float m_FOV = glm::radians(60.f);
		float m_NearClip = 0.01f;
		float m_FarClip = 100.f;
		float m_AspectRatio = 0.f;
	};
}
