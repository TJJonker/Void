#pragma once
#include "Void.h"

class AnimationSystem : public Void::ISystem
{
public:
	virtual void Update(Void::Scene* scene) override;
};

