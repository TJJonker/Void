#include "EditorLayer.h"
#include "imgui.h"


namespace Nebula::Editor {
	EditorLayer::EditorLayer()
	{

	}

	EditorLayer::~EditorLayer()
	{

	}

	void EditorLayer::OnAdded()
	{

	}

	void EditorLayer::OnGuiRender()
	{
		bool tru = true;
		ImGui::ShowDemoWindow(&tru);
	}
}