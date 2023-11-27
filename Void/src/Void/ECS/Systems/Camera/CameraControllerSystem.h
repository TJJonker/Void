#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"
#include <Void/ECS/Components/CameraComponent.h>
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/CameraControllerComponent.h>

namespace Void {
	class CameraControllerSystem : public ISystem
	{
	public:
		virtual void Update(Scene* scene) override;

	private:
		void MoveCamera(CameraControllerComponent& controller, TransformComponent& transform, CameraComponent& camera);
		void RotateCamera(CameraControllerComponent& controller, TransformComponent& transform, CameraComponent& camera);
	};
}
