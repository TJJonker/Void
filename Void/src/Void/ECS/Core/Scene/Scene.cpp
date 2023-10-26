#include "pch.h"
#include "Scene.h"

EntityID Scene::CreateEntity()
{
	// If available, grab one and use it.
	if (!freeEntities.empty()) {

		EntityIndex newEntityIndex = freeEntities.front();
		freeEntities.pop();

		EntityDescription entity = entities[newEntityIndex];
		EntityID newID = CreateEntityId(newEntityIndex, GetEntityVersion(entity.id));

		entities[newEntityIndex].id = newID;
		return newID;
	}

	// If not, create one.
	EntityIndex newIndex = entities.size();
	EntityID newID = CreateEntityId(newIndex, 0);
	entities.push_back({ newID, ComponentMask() });
	return newID;
}

void Scene::DestroyEntity(EntityID id)
{
	EntityID newID = CreateEntityId(-1, GetEntityVersion(id) + 1);
	EntityIndex entityIndex = GetEntityIndex(id);

	entities[entityIndex].id = newID;

	freeEntities.push(entityIndex);
}

bool Scene::IsEntityActive(EntityID id)
{
	return entities[GetEntityIndex(id)].id == id;
}
