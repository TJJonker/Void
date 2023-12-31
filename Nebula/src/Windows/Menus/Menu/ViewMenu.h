#pragma once
#include "Windows/Menus/Core/Menu.h"

namespace Nebula::Window {
	class ViewMenu : public Menu
	{
	public:
		ViewMenu(std::string name, WindowManager* windowManager)
			: Menu(name)
		{
			AddMenuItem("Scene Hierarchy", [windowManager]() {windowManager->OpenWindow("SceneHierarchy"); });
			AddMenuItem("Scene View", [windowManager]() {windowManager->OpenWindow("SceneView"); });
			AddMenuItem("Inspector", [windowManager]() {windowManager->OpenWindow("Inspector"); });
			AddMenuItem("Demo Window", [windowManager]() {windowManager->OpenDemoWindow(); });
		}
	};
}

#pragma once
