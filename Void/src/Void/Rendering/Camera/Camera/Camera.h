#pragma once
#include <glm/glm.hpp>

namespace Void {
	class Camera
	{
	private:
		const float FOV_MIN = 1.0f;
		const float FOV_MAX = 45.0f;

		const float PITCH_MIN = -89.0f;
		const float PITCH_MAX = 89.0f;

		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 8.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		bool m_FirstMouse = true;

		float m_FOV = 45.0f;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;

		glm::vec2 m_LastMousePosition;

		const float m_Sensitivity = 0.1f;
		const float m_CameraSpeed = 2.5f;

	public:
		glm::mat4 GetView() const;
		glm::vec3 GetPosition() const { return m_CameraPosition; }
		glm::vec3 GetCameraFront() const { return m_CameraFront; }

		float GetFOV() const { return m_FOV; }
		void SetFOV(float fov) { m_FOV = fov; }

		void ScrollCamera(float yOffset);
		void LookCamera(const glm::vec2& position);
		void MoveCamera(glm::vec2 movement);
	};
}
