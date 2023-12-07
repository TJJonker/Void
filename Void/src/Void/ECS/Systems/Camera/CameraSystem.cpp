#include "pch.h"
#include "CameraSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include <Void/ECS/Components/CameraComponent.h>
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/Rendering/Components/Renderer/RenderingCommands.h>

namespace Void {
	void CameraSystem::Update(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntitesWith<CameraComponent, TransformComponent>();
		VOID_ASSERT(entities.size() >= 1, "No active camera found.");
		VOID_ASSERT(entities.size() <= 1, "More than one active camera found.");

		Entity* entity = entities[0];
		CameraComponent& camera = entity->GetComponent<CameraComponent>();
		TransformComponent& transform = entity->GetComponent<TransformComponent>();

		Rendering::RenderingCommands::PrepareRender(&camera.SceneCamera, transform.GetTransformMatrix());
	}
}