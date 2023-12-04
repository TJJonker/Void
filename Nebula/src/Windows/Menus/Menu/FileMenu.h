#pragma once
#include "Void.h"
#include "Windows/Menus/Core/Menu.h"

namespace Nebula::Window {
	class FileMenu : public Menu
	{
	public:
		FileMenu(std::string name, WindowManager* windowManager) 
			: Menu(name) 
		{
			Void::SceneManager& currentScene = Void::SceneManager::GetInstance();
			AddMenuItem("Save Scene", [&currentScene]() { currentScene.SaveScene(currentScene.GetCurrentScenePath().c_str()); }, "Ctrl+S");
		}
	};
}

