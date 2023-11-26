#include "pch.h"
#include "EventSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include <Void/ECS/Components/EventTriggerComponent.h>
#include <Void/ECS/Components/EventListenerComponent.h>

namespace Void {
	void EventSystem::Update(Scene* scene)
	{
		std::vector<Entity*> triggerEntities = scene->GetAllEntitesWith<EventTriggerComponent>();

		for (Entity* entity : triggerEntities) {
			EventTriggerComponent& eventTrigger = entity->GetComponent<EventTriggerComponent>();

			for (auto const& event : eventTrigger.Triggers) {
				eventEntities
			}
		}
	}
}
