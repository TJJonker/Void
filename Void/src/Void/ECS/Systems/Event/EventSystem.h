#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"

namespace Void {
	class EventSystem : public ISystem
	{
	public:
		virtual void Update(Scene* scene) override;

	private:
		void ResetEvents(Scene* scene);
	};
}

