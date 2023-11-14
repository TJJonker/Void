#pragma once
#include "Void/Physics/Solvers/Solver.h"

namespace Void {
	class PositionSolver : public Solver
	{
		void Solve(std::vector<Collision>& collisions) override;
	};
}

