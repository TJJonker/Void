#pragma once
#include <Void/ECS/Core/Scene/Scene.h>

class PlayerSystem : public Void::ISystem
{
	void Update(Void::Scene* scene) override;
};

