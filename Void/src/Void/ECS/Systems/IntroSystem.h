#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class IntroSystem : public ISystem
	{
		// Inherited via ISystem
		virtual void Update(Scene* scene) override;
	};
}

