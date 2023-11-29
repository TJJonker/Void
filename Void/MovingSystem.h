#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class MovingSystem : public ISystem
	{
		// Inherited via ISystem
		virtual void Update(Scene* scene) override;
	};
}
