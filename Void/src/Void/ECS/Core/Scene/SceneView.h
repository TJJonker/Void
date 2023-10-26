#pragma once
#include "Void/ECS/Core/Components/ComponentID.h"

template<typename... ComponentTypes>
struct SceneView {

	SceneView(Scene& scene)
		: pScene(&scene)
	{
		if (sizeof...(ComponentTypes) == 0) {
			all = true;
		}
		else {
			int componentIds[] = { GetComponentID<ComponentTypes>() ... };
			for (int i = 0; i < (sizeof...(ComponentTypes)); i++) {
				componentMask.set(componentIds[i]);
			}
		}
	}

	struct Iterator {
		Iterator(Scene* pScene, EntityIndex index, ComponentMask mask, bool all)
			: pScene(pScene), index(index), mask(mask), all(all) { }

		EntityIndex index;
		Scene* pScene;
		ComponentMask mask;
		bool all = false;

		EntityID operator*() const {
			return pScene->entities[index].id;
		}

		bool operator==(const Iterator& other) const {
			return index == other.index || index == pScene->entities.size();
		}

		bool operator!=(const Iterator& other) const {
			return index != other.index && index != pScene->entities.size();
		}

		bool ValidIndex() {
			bool isActive = pScene->IsEntityActive(pScene->entities[index].id);
			return isActive && (all || mask == (mask & pScene->entities[index].mask));
		}

		Iterator& operator++() {
			do {
				index++;
			} while (index < pScene->entities.size() && !ValidIndex());
			return *this;
		}
	};

	const Iterator begin() const {
		int firstIndex = 0;
		bool isActive = pScene->IsEntityActive(pScene->entities[firstIndex].id);
		while (firstIndex < pScene->entities.size() &&
			(componentMask != (componentMask & pScene->entities[firstIndex].mask) || !isActive))
		{
			firstIndex++;
		}
		return Iterator(pScene, firstIndex, componentMask, all);
	}

	const Iterator end() const {
		return Iterator(pScene, EntityIndex(pScene->entities.size()), componentMask, all);
	}


	Scene* pScene = nullptr;
	ComponentMask componentMask;
	bool all = false;
};

