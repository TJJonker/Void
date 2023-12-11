#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"
#include "Void/Physics/Solvers/Solver.h"
#include <Quantum/Quantum.h>
#include "Void/Physics/Solvers/Position/PositionSolver.h"

namespace Void {	 
	class PhysicsSystem : public ISystem
	{
	public:
		PhysicsSystem(Quantum::CollisionHandler& handler)
			: m_Handler(handler) { }

		virtual void Update(Scene* scene) override;

		void AddSolver(std::shared_ptr<Solver> solver) { m_Solvers.push_back(solver); }

	private:
		void ResolveCollisions(Scene* scene);
		void ApplyForces(Scene* scene);

	private:
		unsigned int m_Substeps = 1;
		std::vector<std::shared_ptr<Solver>> m_Solvers;

		Quantum::CollisionHandler& m_Handler;
		PositionSolver m_Solver;
	};
}