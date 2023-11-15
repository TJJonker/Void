#pragma once
#include "Characters/Core/IAbility.h"

struct AbilityNoAbility : public IAbility {
	// Inherited via IAbility
	virtual void Activate() override { }

	virtual float GetCooldownTime() const override 
	{ 
		return 0.0f
	}

	virtual void OnHit() override {	}
};