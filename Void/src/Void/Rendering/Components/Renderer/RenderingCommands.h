#pragma once
#include <glm/glm.hpp>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Renderer.h"
#include <Void/Rendering/Components/Shader/Shader.h>

namespace Void {
	class RenderingCommands {
	private:
		struct RenderData {
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
		};

		static Renderer* m_Renderer;
		static RenderData* m_RenderData;

	public:
		static void Clear();
		static void SetClearColor(const glm::vec4& color);

		static void BeginDraw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		static void Draw(const std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader, glm::mat4 modelMatrix);
	};
}