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

		if (m_SelectedEntity->HasComponent<Void::RenderingComponent>())
			DrawRenderingInspector();
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
			ImGui::DragFloat3("Direction", (float*)&spotLight.SpotLightData.Direction);
			ImGui::DragFloat("Inner Cutoff", &spotLight.SpotLightData.CutOff);
			ImGui::DragFloat("Outer Cutoff", &spotLight.SpotLightData.OuterCutOff);
			ImGui::DragFloat("Constant", &spotLight.SpotLightData.Constant);
			ImGui::DragFloat("Linear", &spotLight.SpotLightData.Linear);
			ImGui::DragFloat("Quadratic", &spotLight.SpotLightData.Quadratic);

			ImGui::Text("Color");
			ImGui::ColorEdit3("Ambient", (float*)&spotLight.SpotLightData.Ambient);
			ImGui::ColorEdit3("Diffuse", (float*)&spotLight.SpotLightData.Diffuse);
		}
	}

	void InspectorWindow::DrawPointLightInspector()
	{
		Void::PointLightComponent& pointLight = m_SelectedEntity->GetComponent<Void::PointLightComponent>();
		if (ImGui::CollapsingHeader("Point Light", ImGuiTreeNodeFlags_None))
		{
			ImGui::Text("Properties");
			ImGui::DragFloat("Constant", &pointLight.pointLightData.Constant);
			ImGui::DragFloat("Linear", &pointLight.pointLightData.Linear);
			ImGui::DragFloat("Quadratic", &pointLight.pointLightData.Quadratic);

			ImGui::Text("Color");
			ImGui::ColorEdit3("Ambient", (float*)&pointLight.pointLightData.Ambient);
			ImGui::ColorEdit3("Diffuse", (float*)&pointLight.pointLightData.Diffuse);
			//ImGui::ColorEdit3("Specular", (float*)&pointLight.pointLightData.Specular);
		}
	}

	void InspectorWindow::DrawRenderingInspector()
	{
		Void::RenderingComponent& rendering = m_SelectedEntity->GetComponent<Void::RenderingComponent>();
		if (ImGui::CollapsingHeader("Rendering", ImGuiTreeNodeFlags_None))
		{
			ImGui::Text("Properties");
			ImGui::Checkbox("Hide texture", &rendering.DrawWireframe);
		}
	}
}