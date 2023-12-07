#pragma once

namespace Quantum {
	std::vector<CollisionPoint> FindSphereSphereColissionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb);
}