#pragma once
#include <Animation/AnimationInfo.h>

struct IVisual {
	virtual AnimationInfo GetAnimationInfo() const = 0;
};