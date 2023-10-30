#pragma once
#include <Void/Vendor/entt/entt.hpp>
#include "Void/Physics/CollisionPoints.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/PhysicsComponent.h>

namespace Void {
	struct Collision {
		TransformComponent& aTransform;
		PhysicsComponent& aPhysics;

		TransformComponent& bTransform;
		PhysicsComponent& bPhysics;

		CollisionPoints* CollisionPoints;
	};
}