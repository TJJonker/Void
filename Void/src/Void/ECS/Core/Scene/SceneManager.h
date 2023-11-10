#pragma once
#include "Scene.h"


namespace Void {
	class SceneManager
	{
	private:
		// Temp raw pointer, should be unique
		Scene* m_CurrentScene;

	public:
		void LoadScene(const char* filePath);
		void SaveScene(const char* filePath);

		// Temp
		void SetScene(Scene* scene) { m_CurrentScene = scene; }

		Scene* GetCurrentScene() { return m_CurrentScene; }
	};
}
