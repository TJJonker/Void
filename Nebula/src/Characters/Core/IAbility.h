#pragma once

class IAbility {
	virtual void Activate() = 0;
	virtual float GetCooldownTime() const = 0;
	virtual void OnHit() = 0;
};