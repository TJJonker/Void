#pragma once
#include <glm/glm.hpp>
#include <string>

namespace Void {
	class Camera {
	public:
		Camera() = default;
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_Projection; }
		void SetSkybox(std::string title) { m_SkyboxTitle = title; }
		std::string GetSkybox() const { return m_SkyboxTitle; }

	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
		std::string m_SkyboxTitle;
	};
}