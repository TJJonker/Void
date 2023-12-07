#include "InspectorWindow.h"
#include "Events/Core/EventManager.h"
#include "Events/Commands/SetCurrentEntity/SetCurrentEntityCommand.h"

namespace Nebula::Window {
	void InspectorWindow::OnAdded()
	{
		p_Name = "Inspector";

		Events::EventManager::GetInstance().EntitySelectedEvent.AddCommand(new Events::SetCurrentEntityCommand(&m_SelectedEntity));
	}

	void InspectorWindow::OnGuiRender()
	{
		if (m_SelectedEntity == nullptr)
			return;

		char entityName[32];
		strcpy_s(entityName, m_SelectedEntity->Name.c_str());
		ImGui::InputText("EntityName", entityName, 32);
		entityName[strlen(entityName)] = NULL;
		m_SelectedEntity->Name = entityName;

		if(m_SelectedEntity->HasComponent<Void::TransformComponent>())
			DrawTransformInspector();

		if (m_SelectedEntity->HasComponent<Void::SpotLightComponent>())
			DrawSpotLightInspector();

		if (m_SelectedEntity->HasComponent<Void::PointLightComponent>())
			DrawPointLightInspector();
	}

	void InspectorWindow::DrawTransformInspector()
	{
		Void::TransformComponent& transform = m_SelectedEntity->GetComponent<Void::TransformComponent>();
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_None))
		{
			ImGui::DragFloat3("Position", (float*)&transform.Position);
			glm::vec3 rotationInDegrees = { glm::degrees(transform.Rotation.x), glm::degrees(transform.Rotation.y) , glm::degrees(transform.Rotation.z) };
			ImGui::DragFloat3("Rotation", (float*)&rotationInDegrees);
			transform.Rotation = { glm::radians(rotationInDegrees.x), glm::radians(rotationInDegrees.y) , glm::radians(rotationInDegrees.z) };
			ImGui::DragFloat3("Scale", (float*)&transform.Scale);
		}		
	}

	void InspectorWindow::DrawSpotLightInspector()
	{
		Void::SpotLightComponent& spotLight = m_SelectedEntity->GetComponent<Void::SpotLightComponent>();
		if (ImGui::CollapsingHeader("Spotlight", ImGuiTreeNodeFlags_None))
		{
			ImGui::Text("Properties");
			ImGui::DragFloat3("Direction", (float*)&spotLight.Direction);
			ImGui::DragFloat("Inner Cutoff", &spotLight.CutOff);
			ImGui::DragFloat("Outer Cutoff", &spotLight.OuterCutOff);
			ImGui::DragFloat("Constant", &spotLight.Constant);
			ImGui::DragFloat("Linear", &spotLight.Linear);
			ImGui::DragFloat("Quadratic", &spotLight.Quadratic);

			ImGui::Text("Color");
			ImGui::ColorEdit3("Ambient", (float*)&spotLight.Ambient);
			ImGui::ColorEdit3("Diffuse", (float*)&spotLight.Diffuse);
			ImGui::ColorEdit3("Specular", (float*)&spotLight.Specular);
		}
	}

	void InspectorWindow::DrawPointLightInspector()
	{
		Void::PointLightComponent& pointLight = m_SelectedEntity->GetComponent<Void::PointLightComponent>();
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_None))
		{
			ImGui::Text("Properties");
			ImGui::DragFloat("Constant", &pointLight.Constant);
			ImGui::DragFloat("Linear", &pointLight.Linear);
			ImGui::DragFloat("Quadratic", &pointLight.Quadratic);

			ImGui::Text("Color");
			ImGui::ColorEdit3("Ambient", (float*)&pointLight.Ambient);
			ImGui::ColorEdit3("Diffuse", (float*)&pointLight.Diffuse);
			ImGui::ColorEdit3("Specular", (float*)&pointLight.Specular);
		}
	}
}