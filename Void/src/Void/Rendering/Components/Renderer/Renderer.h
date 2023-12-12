#pragma once
#include "Void/Rendering/Components/VertexArray/VertexArray.h"
#include <Void/Rendering/Components/Camera/Core/Camera.h>
#include "PointLightData.h"

namespace Void::Rendering {

	class Renderer {
	public:
		enum class API {
			None, OpenGL
		};

	private:
		static API m_RendererAPI;

	public:
		virtual void Initialize() = 0;

		virtual void Submit(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName, bool showTexture) = 0;
		virtual void SubmitBlended(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName) = 0;
		virtual void SubmitPointLight(const PointLightData& pointLight) = 0;

		virtual void PrepareRender(const Camera* camera, const glm::mat4& transformMatrix) = 0;
		virtual void PrepareRender(const glm::mat4& viewProjectionMatrix, const glm::vec3& position, std::string skyboxTitle) = 0;
		virtual void Render() = 0;
		virtual void FinishRender() = 0;
		virtual void ResetSubmissions() = 0;

		virtual void Flush() = 0;

		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		static API GetAPI() { return m_RendererAPI; }
	};
}