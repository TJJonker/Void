#pragma once
#include "Void/Physics/Collision.h"

namespace Void {
	class Solver
	{
	public:
		virtual void Solve(std::vector<Collision>& collisions) = 0;
	};
}
