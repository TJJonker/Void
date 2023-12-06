#include "pch.h"
#include "CameraControllerSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"



namespace Void {
	void CameraControllerSystem::Update(Scene* scene)
	{

		std::vector<Entity*> entities = scene->GetAllEntitesWith<CameraComponent, TransformComponent, CameraControllerComponent>();

		for (Entity* entity : entities) {
            CameraComponent& camera = entity->GetComponent<CameraComponent>();
            TransformComponent& transform = entity->GetComponent<TransformComponent>();
            CameraControllerComponent& controller = entity->GetComponent<CameraControllerComponent>();

            MoveCamera(controller, transform, camera);
            RotateCamera(controller, transform, camera);
		}
	}

    void CameraControllerSystem::MoveCamera(CameraControllerComponent& controller, TransformComponent& transform, CameraComponent& camera)
    {
        int moveX = Input::KeyDown(controller.KeyRight) - Input::KeyDown(controller.KeyLeft);
        int moveZ = Input::KeyDown(controller.KeyForward) - Input::KeyDown(controller.KeyBackward);

        const float cameraMovementSpeed = controller.MovementSpeed * Time::DeltaTime();

        glm::vec3 XZCamera = transform.GetForwardVector();
        XZCamera.y = 0;
        XZCamera = glm::normalize(XZCamera);
        transform.Position += cameraMovementSpeed * XZCamera * (float)moveZ;
        transform.Position += glm::normalize(glm::cross(transform.GetForwardVector(), transform.GetUpVector())) * cameraMovementSpeed * (float)moveX;
    }

    void CameraControllerSystem::RotateCamera(CameraControllerComponent& controller, TransformComponent& transform, CameraComponent& camera)
    {
        static bool firstMouse = true;
        static glm::vec2 lastMousePosition;

        #define PITCH_MAX 89.f
        #define PITCH_MIN -89.f

        glm::vec2 mousePosition = Input::MousePosition();
        if (firstMouse) {
            lastMousePosition = mousePosition;
            firstMouse = false;
        }

        glm::vec2 offset = { mousePosition.x - lastMousePosition.x, lastMousePosition.y - mousePosition.y };
        offset *= controller.Sensitivity * Time::DeltaTime();
        lastMousePosition = mousePosition;

        transform.Rotation.y += offset.x;
        transform.Rotation.x += offset.y;
        transform.Rotation.x = glm::clamp(transform.Rotation.x, PITCH_MIN, PITCH_MAX);
    }
}
