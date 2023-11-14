#include "pch.h"
#include "RenderingCommands.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Void::Rendering {

	RenderingCommands::RenderData* RenderingCommands::m_RenderData = new RenderingCommands::RenderData();
	std::vector<RenderingCommands::PointLightData> RenderingCommands::m_PointLightData = {};
	std::vector<RenderingCommands::SpotLightData> RenderingCommands::m_SpotLightData = {};

	void RenderingCommands::SetClearColor(const glm::vec4& color)
	{
		m_Renderer->SetClearColor(color);
	}

	void RenderingCommands::Clear()
	{
		m_Renderer->Clear();
	}

	void RenderingCommands::AddPointLight(PointLightData pointLightData)
	{
		m_PointLightData.push_back(pointLightData);
	}

	void RenderingCommands::AddSpotLight(SpotLightData spotLightData)
	{
		m_SpotLightData.push_back(spotLightData);
	}

	void RenderingCommands::BeginDraw(Camera* camera)
	{
		m_RenderData->viewMatrix = camera->GetView();
		m_RenderData->projectionMatrix = glm::perspective(glm::radians(camera->GetFOV()), 1280.0f / 720.0f, 0.1f, 100.0f);
		m_RenderData->viewPosition = camera->GetPosition();
	}

	void RenderingCommands::Draw(VertexArray* vertexArray, Shader* shader, glm::mat4 modelMatrix)
	{
		shader->Bind();
		shader->SetMatrix4("viewMatrix", m_RenderData->viewMatrix);
		shader->SetMatrix4("projectionMatrix", m_RenderData->projectionMatrix);
		shader->SetMatrix4("modelMatrix", modelMatrix);
		//shader->SetVec3("viewPosition", m_RenderData->viewPosition);

		/// TODO: TEMP
		glm::vec3 lightDirection = { .2f, 0.f, -1.f };
		glm::vec3 ambientColor = { .4f, .4f, .4f };
		glm::vec3 diffuseColor = { .6f, .6f, .6f };
		glm::vec3 specularColor = { 1.f, 1.f, 1.f };

		// TODO: Temp as well
		for (int i = 0; i < m_PointLightData.size(); i++) {
			std::ostringstream str;
			str << "pointLights[" << i << "]";
			shader->SetVec3(str.str() + ".position", m_PointLightData[i].Position);
			shader->SetFloat(str.str() + ".constant", m_PointLightData[i].Constant);
			shader->SetFloat(str.str() + ".linear", m_PointLightData[i].Linear);
			shader->SetFloat(str.str() + ".quadratic", m_PointLightData[i].Quadratic);
			shader->SetVec3(str.str() + ".ambient", m_PointLightData[i].Ambient);
			shader->SetVec3(str.str() + ".diffuse", m_PointLightData[i].Diffuse);
		}

		// TODO: Temp as well
		for (int i = 0; i < m_SpotLightData.size(); i++) {
			std::ostringstream str;
			str << "spotLights[" << i << "]";
			shader->SetVec3(str.str() + ".ambient", m_SpotLightData[i].Ambient);
			shader->SetFloat(str.str() + ".constant", m_SpotLightData[i].Constant);
			shader->SetVec3(str.str() + ".diffuse", m_SpotLightData[i].Diffuse);
			shader->SetFloat(str.str() + ".linear", m_SpotLightData[i].Linear);
			shader->SetFloat(str.str() + ".quadratic", m_SpotLightData[i].Quadratic);
			shader->SetVec3(str.str() + ".position", m_SpotLightData[i].Position);
			shader->SetFloat(str.str() + ".cutOff", m_SpotLightData[i].CutOff);
			shader->SetVec3(str.str() + ".direction", m_SpotLightData[i].Direction);
			shader->SetFloat(str.str() + ".outerCutOff", m_SpotLightData[i].OuterCutOff);
			shader->SetVec3(str.str() + ".specular", m_SpotLightData[i].Specular);
		}

		shader->SetVec3("directionalLight.direction", lightDirection);
		shader->SetVec3("directionalLight.ambient", ambientColor);
		shader->SetVec3("directionalLight.diffuse", diffuseColor);
		shader->SetVec3("directionalLight.specular", specularColor);
		///

		vertexArray->Bind();
		m_Renderer->Draw(vertexArray);
	}
}