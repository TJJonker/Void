#pragma once
#include "Void/Physics/CollisionPoints.h"
#include <Void/ECS/Core/Entity/Entity.h>
#include <Quantum/Quantum.h>

namespace Void {
	struct Collision {
		Entity* A;
		Entity* B;			
		Quantum::CollisionInfo CollisionPoint;
	};
}