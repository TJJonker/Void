#pragma once
#include "Void/Physics/Solvers/Solver.h"

namespace Void {
	class ImpulseSolver : public Solver
	{
		void Solve(std::vector<Collision>& collisions) override;
	};
}

