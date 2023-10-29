#pragma once
#include "Void/Vendor/entt/entt.hpp"

namespace Void {
	class ISystem {
	public:
		virtual void Update(entt::registry& registry) = 0;
	};
}