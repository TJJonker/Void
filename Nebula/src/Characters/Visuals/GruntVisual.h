#pragma once
#include "Characters/Core/IVisual.h"

struct GruntVisual : public IVisual {

	AnimationInfo m_AnimationInfo;

	GruntVisual() {
		m_AnimationInfo.AnimationFrames[AnimationInfo::Direction::LEFT] = {
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt2.ply",
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt3.ply"
		};

		m_AnimationInfo.AnimationFrames[AnimationInfo::Direction::UP] = {
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt2.ply",
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt3.ply"
		};

		m_AnimationInfo.AnimationFrames[AnimationInfo::Direction::RIGHT] = {
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt2.ply",
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt3.ply"
		};

		m_AnimationInfo.AnimationFrames[AnimationInfo::Direction::DOWN] = {
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt2.ply",
			"Temp/Models/Grunt/grunt1.ply",
			"Temp/Models/Grunt/grunt3.ply"
		};
	}

	AnimationInfo GetAnimationInfo() const override {
		return m_AnimationInfo;
	}
};