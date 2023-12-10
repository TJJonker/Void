#pragma once
#include <glm/glm.hpp>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Renderer.h"
#include <Void/Rendering/Components/Shader/Shader.h>
#include <Void/Rendering/Components/Camera/Core/Camera.h>

namespace Void::Rendering {
	class RenderingCommands {
	public:
		//struct PointLightData {
		//	glm::vec3 Position = glm::vec3(0);
		//	float Constant = 1.0f;
		//	float Linear = 0.09f;
		//	float Quadratic = 0.032f;
		//	glm::vec3 Ambient = glm::vec3(0);
		//	glm::vec3 Diffuse = glm::vec3(0);
		//};

		//struct SpotLightData {
		//	glm::vec3 Position = glm::vec3(0); 
		//	glm::vec3 Direction = normalize(glm::vec3(0.0, -1.0, 0.0));
		//	float CutOff = (float)glm::radians(15.0);
		//	float OuterCutOff = (float)glm::radians(30.0);
		//	float Constant = 1.0f;
		//	float Linear = 0.09f;
		//	float Quadratic = 0.032f;
		//	glm::vec3 Ambient = glm::vec3(0.2, 0.2, 0.2);
		//	glm::vec3 Diffuse = glm::vec3(0.8, 0.8, 0.6);
		//	glm::vec3 Specular = glm::vec3(1.0, 1.0, 1.0);
		//};

	private:
		//struct RenderData {
		//	glm::mat4 projectionMatrix;
		//	glm::mat4 viewMatrix;
		//	glm::vec3 viewPosition;
		//};

		static Renderer* m_Renderer;
		//static RenderData* m_RenderData;
		//static std::vector<PointLightData> m_PointLightData;
		//static std::vector<SpotLightData> m_SpotLightData;

	public:
		static void Initialize();

		static void Submit(VertexArray* vertexArray, glm::mat4 modelMatrix, std::vector<std::string> textureNames, std::string shaderName);
		static void SubmitBlended(VertexArray* vertexArray, glm::mat4 modelMatrix, std::vector<std::string> textureNames, std::string shaderName);

		static void SubmitDebugRectangle(const glm::mat4& transform, const glm::vec4& color);

		static void PrepareRender(const Camera* camera, const glm::mat4& transformMatrix);
		static void PrepareRender(const glm::mat4& viewProjectionMatrix, const glm::vec3& position, std::string skyboxTitle = "");
		static void Render();
		static void FinishRender();

		static void ResetSubmissions();

		static void Clear();
		static void SetClearColor(const glm::vec4& color);

		//static void AddPointLight(PointLightData pointLightData);
		//static void AddSpotLight(SpotLightData spotLightData);
	};
}