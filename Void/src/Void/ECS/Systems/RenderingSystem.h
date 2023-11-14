#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void::Rendering {

	class RenderingSystem : public ISystem
	{
		void Update(Scene* scene) override;
	};

}