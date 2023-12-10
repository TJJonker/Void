#pragma once
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include <Void/Rendering/Components/Shader/Shader.h>

namespace Void::Rendering {
	struct BatchSubmission {
		VertexArray* VertexArray;
		glm::mat4 ModelMatrix;
		std::vector<std::string> TextureNames;
	};

	class OpenGLRenderer : public Renderer
	{
	public:
		void Initialize();
				
		virtual void PrepareRender(const Camera* camera, const glm::mat4& transformMatrix) override;
		virtual void PrepareRender(const glm::mat4& viewProjectionMatrix, const glm::vec3& position, std::string skyboxTitle) override;
		virtual void FinishRender() override;
		void ResetSubmissions();
		
		virtual void Submit(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName) override;
		virtual void SubmitBlended(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName) override;

		virtual void Render() override;
		void Flush();

		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

	private:
		unsigned int NewTexturesCount(std::vector<std::string> textureNames);
		void PrepareRenderData();
		void ExecuteRender(const std::pair<std::string, std::vector<BatchSubmission>>&);

	private:
		std::map<std::string, std::vector<BatchSubmission>> m_Submissions;
		std::map<std::string, std::vector<BatchSubmission>> m_SubmissionsBlended;

		// Inherited via Renderer
		void DrawDebugRectangle(const glm::mat4& transform, const glm::vec4& color) override;
	};
}
