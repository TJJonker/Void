#pragma once
#include "Characters/Core/IMovement.h"
#include "Characters/Core/IAbility.h"
#include "Characters/Core/IVisual.h"

struct CharacterFactory {
	virtual IMovement* CreateMovement() = 0;
	virtual IVisual* CreateModel() = 0;
	virtual IAbility* CreateAbility() = 0;
};