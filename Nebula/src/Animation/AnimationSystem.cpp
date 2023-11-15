#include "AnimationSystem.h"
#include "Animation/AnimationComponent.h"
#include "Void.h"

void AnimationSystem::Update(Void::Scene* scene)
{
	for (Void::Entity* entity : scene->GetAllEntitesWith<AnimationComponent, Void::RenderingComponent, Void::TransformComponent>()) {
		Void::RenderingComponent& rendering = entity->GetComponent<Void::RenderingComponent>();
		AnimationComponent& animation = entity->GetComponent<AnimationComponent>();
		Void::TransformComponent& transform = entity->GetComponent<Void::TransformComponent>();

		glm::vec3 direction = transform.Position - animation.GetLastPosition();
		animation.SetLastPosition(transform.Position);
		animation.UpdateFrameTimer();

		Void::RenderingComponent::Submesh submesh;
		submesh.Model = animation.GetAnimationFrame(animation.GetAnimationDirectionXZ(direction));
		submesh.Shader = animation.GetShader();
		submesh.Textures.push_back(animation.GetTexture());
		rendering.Submeshes.push_back(submesh);
	}
}
