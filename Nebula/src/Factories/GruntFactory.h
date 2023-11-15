#pragma once
#include "CharacterFactory.h"
#include "Characters/Movement/MovementFollowPlayer.h"
#include "Characters/Visuals/GruntVisual.h"
#include "Characters/Abilities/AbilityNoAbility.h"

struct GruntFactory : public CharacterFactory {
	virtual IMovement* CreateMovement() override {
		return new MovementFollowPlayer();
	}

	virtual IVisual* CreateModel() override {
		return new GruntVisual();
	}

	virtual IAbility* CreateAbility() override {
		return new AbilityNoAbility();
	}
};
