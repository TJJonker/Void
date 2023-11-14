#pragma once

namespace Void {
	// Forward declaration
	class Scene;

	class ISystem {
	public:
		virtual void Update(Scene* scene) = 0;
	};
}