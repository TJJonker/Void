#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class AudioListenerSystem : public ISystem
	{
		virtual void Update(Scene* scene) override;
	};
}