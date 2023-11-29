#include "pch.h"
#include "EventSystem.h"
#include "Void/ECS/Core/Scene/Scene.h"
#include <Void/ECS/Components/EventListenerComponent.h>

namespace Void {
	typedef std::map<ECSEventType, std::vector<IECSEventInfo>> EntityEvents;
	typedef std::map<ECSEventType, std::vector<IECSCommand*>> Events;

	void EventSystem::Update(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntitesWith<EventListenerComponent>();

		for (Entity* entity : entities) {			
			EntityEvents entityEvents = entity->GetEvents();
			EventListenerComponent& listenerEvents = entity->GetComponent<EventListenerComponent>();

			for (const auto& event : listenerEvents.Events) {
				if (!entityEvents.count(event.first)) continue;

				for (IECSCommand* command : event.second)
					for (IECSEventInfo info : entityEvents[event.first])
						command->Execute(info);

			}
					
		}

		ResetEvent(scene);
	}

	void EventSystem::ResetEvents(Scene* scene)
	{
		std::vector<Entity*> entities = scene->GetAllEntities();
		for (Entity* entity : entities)
			entity->ResetEvents();
	}
}
