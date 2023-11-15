#pragma once
#include "Builder/Core/AbstractCharacterBuilder.h"
#include "Void.h"

class CharacterBuilder : public AbstractCharacterBuilder
{
private:
	Void::Entity* m_Entity;

public:
	virtual void Reset() override;
	virtual Void::Entity* GetResult() override { return m_Entity; }

	virtual void AddVisual(IVisual* visual) override;
	virtual void AddMovement(IMovement* movement) override;
	virtual void AddAbility(IAbility* ability) override;
};

