#pragma once
#include "Scene.h"
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	class SceneManager
	{

	private:
		ISerializable* DeserializeComponent(std::string componentName, Entity* entity);


	public:
		void LoadScene(const char* filePath);
		void SaveScene(const char* filePath);

		std::string GetCurrentScenePath() { return m_CurrentScenePath; }

		Scene* GetCurrentScene() { return m_CurrentScene; }
		static SceneManager& GetInstance();

	private:
		Scene* m_CurrentScene;
		std::string m_CurrentScenePath;
	};
}
