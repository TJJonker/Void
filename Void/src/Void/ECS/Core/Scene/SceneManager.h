#pragma once
#include "Scene.h"
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	class SceneManager
	{
	private:
		// Temp raw pointer, should be unique
		Scene* m_CurrentScene;

	private:
		ISerializable* DeserializeComponent(std::string componentName, Scene* scene, entt::entity entity);


	public:
		void LoadScene(const char* filePath);
		void SaveScene(const char* filePath);

		Scene* GetCurrentScene() { return m_CurrentScene; }
	};
}
