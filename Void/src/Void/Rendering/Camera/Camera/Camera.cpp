#include "pch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Void/Utils/TimeSteps/Time.h"

namespace Void {
    glm::mat4 Camera::GetView() const
    {
        return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
    }

    void Camera::ScrollCamera(float yOffset)
    {
        m_FOV -= yOffset;
        m_FOV = std::max(FOV_MIN, std::min(m_FOV, FOV_MAX));
    }

    void Camera::LookCamera(const glm::vec2& position)
    {
        if (m_FirstMouse) {
            m_LastMousePosition = position;
            m_FirstMouse = false;
        }

        glm::vec2 offset = { position.x - m_LastMousePosition.x, m_LastMousePosition.y - position.y }; 
        m_LastMousePosition = position; 

        offset *= m_Sensitivity; 

        m_Yaw += offset.x; 
        m_Pitch += offset.y; 

        m_Pitch = std::max(PITCH_MIN, std::min(m_Pitch, PITCH_MAX)); 

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)); 
        direction.y = sin(glm::radians(m_Pitch)); 
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)); 
        m_CameraFront = glm::normalize(direction); 
    }

    void Camera::MoveCamera(glm::vec2 movement)
    {
        const float cameraMovementSpeed = m_CameraSpeed * Time::DeltaTime();

        m_CameraPosition += cameraMovementSpeed * m_CameraFront * movement.y;
        m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraMovementSpeed * movement.x;
    }
}