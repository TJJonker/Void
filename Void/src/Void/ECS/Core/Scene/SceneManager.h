#pragma once
#include "Scene.h"


namespace Void {
	class SceneManager
	{
	private:
		std::unique_ptr<Scene> m_CurrentScene;

	public:
		void LoadScene(const char* filePath);
		void SaveScene(const char* filePath);

		Scene* GetCurrentScene() { return m_CurrentScene.get(); }
	};
}
