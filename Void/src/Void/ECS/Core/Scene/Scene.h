#pragma once
#include <queue>
#include <bitset>
#include <vector>
#include "Void/ECS/Core/Entity/Entity.h"
#include "Void/ECS/Core/Components/ComponentID.h"
#include "Void/ECS/Core/Components/ComponentPool.h"

struct TestComponent {
	float position{ 1.0f };
	float rotation{ 2.0f };
};

const int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

struct Scene {
	struct EntityDescription {
		EntityID id;
		ComponentMask mask;
	};

	std::vector<EntityDescription> entities;
	std::queue<EntityIndex> freeEntities;
	std::vector<ComponentPool*> componentPools;

	EntityID CreateEntity();
	void DestroyEntity(EntityID id);
	bool IsEntityActive(EntityID id);

	template<typename T>
	T* AddComponent(EntityID id) 
	{
		if (!IsEntityActive(id))
			return nullptr;

		int componentID = GetComponentID<T>();

		if (componentPools.size() <= componentID)
			componentPools.resize(componentID + 1, new ComponentPool(sizeof(T)));
		if (componentPools[componentID] == nullptr)
			componentPools[componentID] = new ComponentPool(sizeof(T));

		T* component = new (componentPools[componentID]->Get(GetEntityIndex(id))) T();

		entities[GetEntityIndex(id)].mask.set(componentID);
		return component;
		//return nullptr;
	};

	template<typename T>
	void RemoveComponent(EntityID id) {
		if (!IsEntityActive(id))
			return;

		int componentID = GetComponentID<T>();
		entities[GetEntityIndex(id)].mask.set(componentID, false);
	}

	template<typename T>
	T* GetComponent(EntityID id) {
		
		if (!IsEntityActive(id))
			return nullptr;

		int componentID = GetComponentID<T>();
		EntityIndex entityIndex = GetEntityIndex(id);

		if (!entities[entityIndex].mask.test(componentID))
			return nullptr;

		T* component = static_cast<T*>(componentPools[componentID]->Get(entityIndex));
		return component;
	}
};