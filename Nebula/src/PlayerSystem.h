#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

class PlayerSystem : public Void::ISystem
{
	void Update(entt::registry& registry) override;
};

