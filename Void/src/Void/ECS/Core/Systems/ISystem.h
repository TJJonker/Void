#pragma once
#include <Void/ECS/Core/Scene/Scene.h>
#include <Void/ECS/Core/Scene/SceneView.h>

namespace Void {
	class ISystem {
	public:
		virtual void Update(Scene scene) = 0;
	};
}