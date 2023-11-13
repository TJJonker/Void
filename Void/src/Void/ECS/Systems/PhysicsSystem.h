#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"
#include "Void/Physics/Solvers/Solver.h"

namespace Void {
	class PhysicsSystem : public ISystem
	{
	private:
		unsigned int m_Substeps = 1;
		std::vector<std::shared_ptr<Solver>> m_Solvers;

		void ResolveCollisions(entt::registry& registry);
		void ApplyForces(entt::registry& registry);

	public:
		void Update(entt::registry& registry) override;
		void AddSolver(std::shared_ptr<Solver> solver) { m_Solvers.push_back(solver); }
	};
}