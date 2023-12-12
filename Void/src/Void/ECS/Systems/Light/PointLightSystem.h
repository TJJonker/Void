#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class PointLightSystem : public ISystem
	{
		void Update(Scene* scene) override;
	};
}

