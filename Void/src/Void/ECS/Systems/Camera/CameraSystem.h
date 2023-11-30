#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class CameraSystem : public ISystem
	{
		virtual void Update(Scene* scene) override;
	};
}
