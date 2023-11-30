#pragma once
#include "IECSEventInfo.h"
#include "Void/ECS/Core/Entity/Entity.h"
#include "Void/Physics/CollisionPoints.h"

namespace Void {
	struct CollisionInfo : public IECSEventInfo {
		CollisionInfo(Entity* other, CollisionPoint cp)
			: Other(other), CollisionPoint(cp) { }

		Entity* Other;
		CollisionPoint CollisionPoint;
	};
}