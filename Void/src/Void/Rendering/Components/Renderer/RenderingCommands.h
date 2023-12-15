#pragma once
#include <glm/glm.hpp>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Renderer.h"
#include <Void/Rendering/Components/Shader/Shader.h>
#include <Void/Rendering/Components/Camera/Core/Camera.h>

namespace Void::Rendering {
	class RenderingCommands {

	private:
		static Renderer* m_Renderer;

	public:
		static void Initialize();

		static void Submit(VertexArray* vertexArray, glm::mat4 modelMatrix, std::vector<std::string> textureNames, std::string shaderName, bool showTexture);
		static void SubmitBlended(VertexArray* vertexArray, glm::mat4 modelMatrix, std::vector<std::string> textureNames, std::string shaderName);

		static void SubmitPointLight(const PointLightData& pointLight);
		static void SubmitSpotLight(const SpotLightData& spotLight);

		static void PrepareRender(const Camera* camera, const glm::mat4& transformMatrix);
		static void PrepareRender(const glm::mat4& viewProjectionMatrix, const glm::vec3& position, std::string skyboxTitle = "");
		static void Render();
		static void FinishRender();

		static void ResetSubmissions();

		static void Clear();
		static void SetClearColor(const glm::vec4& color);
	};
}