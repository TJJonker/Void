#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {

	class RenderingSystem : public ISystem
	{
		void Update(entt::registry& registry) override;
	};

}