#include "pch.h"
#include "RenderingCommands.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Void/Rendering/Components/Texture/Texture.h>

namespace Void::Rendering {	

	void RenderingCommands::Initialize()
	{
		m_Renderer->Initialize();
	}

	void RenderingCommands::Submit(VertexArray* vertexArray, glm::mat4 modelMatrix, std::vector<std::string> textureNames, std::string shaderName)
	{
		m_Renderer->Submit(vertexArray, modelMatrix, textureNames, shaderName);
	}

	void RenderingCommands::SubmitBlended(VertexArray* vertexArray, glm::mat4 modelMatrix, std::vector<std::string> textureNames, std::string shaderName)
	{
		m_Renderer->SubmitBlended(vertexArray, modelMatrix, textureNames, shaderName);
	}

	void RenderingCommands::PrepareRender(const Camera* camera, const glm::mat4& transformMatrix)
	{
		m_Renderer->PrepareRender(camera, transformMatrix);
	}

	void RenderingCommands::PrepareRender(const glm::mat4& viewProjectionMatrix, const glm::vec3 cameraPosition)
	{
	}

	void RenderingCommands::Render()
	{
		m_Renderer->Render();
	}

	void RenderingCommands::FinishRender()
	{
		m_Renderer->FinishRender();
	}

	void RenderingCommands::ResetSubmissions()
	{
		m_Renderer->ResetSubmissions();
	}

	void RenderingCommands::Clear()
	{
		m_Renderer->Clear();
	}

	void RenderingCommands::SetClearColor(const glm::vec4& color)
	{
		m_Renderer->SetClearColor(color);
	}

	//RenderingCommands::RenderData* RenderingCommands::m_RenderData = new RenderingCommands::RenderData();
	//std::vector<RenderingCommands::PointLightData> RenderingCommands::m_PointLightData = {};
	//std::vector<RenderingCommands::SpotLightData> RenderingCommands::m_SpotLightData = {};

	//void RenderingCommands::SetClearColor(const glm::vec4& color)
	//{
	//	m_Renderer->SetClearColor(color);
	//}

	//void RenderingCommands::Clear()
	//{
	//	m_Renderer->Clear();
	//}

	//void RenderingCommands::AddPointLight(PointLightData pointLightData)
	//{
	//	m_PointLightData.push_back(pointLightData);
	//}

	//void RenderingCommands::AddSpotLight(SpotLightData spotLightData)
	//{
	//	m_SpotLightData.push_back(spotLightData);
	//}

	//void RenderingCommands::BeginDraw(const glm::mat4& view, float fov, const glm::vec3& position)
	//{
	//	m_RenderData->viewMatrix = view;
	//	m_RenderData->projectionMatrix = glm::perspective(glm::radians(fov), 1280.0f / 720.0f, 0.1f, 100.0f);
	//	m_RenderData->viewPosition = position;
	//}

	//void RenderingCommands::Draw(VertexArray* vertexArray, Shader* shader, glm::mat4 modelMatrix)
	//{
	//	shader->Bind();
	//	shader->SetMatrix4("viewMatrix", m_RenderData->viewMatrix);
	//	shader->SetMatrix4("projectionMatrix", m_RenderData->projectionMatrix);
	//	shader->SetMatrix4("modelMatrix", modelMatrix);
	//	//shader->SetVec3("viewPosition", m_RenderData->viewPosition);

	//	/// TODO: TEMP
	//	glm::vec3 lightDirection = { .2f, 0.f, -1.f };
	//	glm::vec3 ambientColor = { .4f, .4f, .4f };
	//	glm::vec3 diffuseColor = { .6f, .6f, .6f };
	//	glm::vec3 specularColor = { 1.f, 1.f, 1.f };

	//	m_Renderer->Draw(vertexArray);
	//}
}