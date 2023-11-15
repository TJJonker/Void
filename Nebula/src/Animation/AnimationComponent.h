#pragma once
#include "AnimationInfo.h"

class AnimationComponent {

private:
	AnimationInfo m_AnimationInfo;

	glm::vec3 m_LastPositon;

	unsigned int m_CurrentFrame = 0;

	float m_FrameTimer = 0.f;
	float m_TimePerFrame = .5f;

public:
	void SetLastPosition(glm::vec3 position) { m_LastPositon = position; }
	glm::vec3 GetLastPosition() const { return m_LastPositon; }

	AnimationInfo::Direction GetAnimationDirectionXZ(glm::vec3 direction) {
		if (direction.z < 0)
			return AnimationInfo::Direction::UP;
		if (direction.z > 0)
			return AnimationInfo::Direction::DOWN;
		if (direction.x > 0)
			return AnimationInfo::Direction::RIGHT;
		if (direction.x < 0)
			return AnimationInfo::Direction::LEFT;
	}

	void SetAnimationInfo(AnimationInfo animationInfo) { m_AnimationInfo = animationInfo; }

	std::string GetAnimationFrame(const AnimationInfo::Direction direction) {
		std::vector<std::string> strings = m_AnimationInfo.AnimationFrames.at(direction);
		unsigned int index = m_CurrentFrame % strings.size();
		return strings[index];
	}

	void UpdateFrameTimer() {
		m_FrameTimer += Void::Time::DeltaTime();
		if (m_FrameTimer > m_TimePerFrame) {
			m_FrameTimer -= m_TimePerFrame;
			m_CurrentFrame++;
		}
	}

	std::string GetShader() const { return m_AnimationInfo.Shader; }

	std::string GetTexture() const { return m_AnimationInfo.Texture; }
};