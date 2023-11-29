#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class AudioListenerSystem : public ISystem
	{
	public:
		virtual void Update(Scene* scene) override;
	};
}