#include "CharacterBuilder.h"
#include <Animation/AnimationComponent.h>

void CharacterBuilder::Reset()
{
	m_Entity = Void::Scene::GetInstance().CreateEntity();
}

void CharacterBuilder::AddVisual(IVisual* visual)
{
	m_Entity->AddComponent<Void::TransformComponent>();
	Void::RenderingComponent& rendering = m_Entity->AddComponent<Void::RenderingComponent>();
	AnimationComponent& animation = m_Entity->AddComponent<AnimationComponent>();
	animation.SetAnimationInfo(visual->GetAnimationInfo());
}

void CharacterBuilder::AddMovement(IMovement* movement)
{

}

void CharacterBuilder::AddAbility(IAbility* ability)
{

}
