#pragma once
#include "Void/Physics/CollisionPoints.h"
#include <Void/ECS/Core/Entity/Entity.h>

namespace Void {
	struct Collision {
		Entity* A;
		Entity* B;			
		CollisionPoint CollisionPoint;
	};
}