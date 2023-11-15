#pragma once
#include "Void.h"
#include <Characters/Core/IVisual.h>
#include <Characters/Core/IMovement.h>
#include <Characters/Core/IAbility.h>

class AbstractCharacterBuilder
{
	virtual void Reset() = 0;
	virtual Void::Entity* GetResult() = 0;

	virtual void AddVisual(IVisual* visual) = 0;
	virtual void AddMovement(IMovement* movement) = 0;
	virtual void AddAbility(IAbility* ability) = 0;
};

