#pragma once
#include <glm/glm.hpp>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Renderer.h"
#include <Void/Rendering/Components/Shader/Shader.h>
#include <Void/Rendering/Camera/Camera/Camera.h>

namespace Void::Rendering {
	class VOID_API RenderingCommands {
	private:
		struct RenderData {
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::vec3 viewPosition;
		};

		static Renderer* m_Renderer;
		static RenderData* m_RenderData;

	public:
		static void Clear();
		static void SetClearColor(const glm::vec4& color);

		static void BeginDraw(Camera* camera);
		static void Draw(VertexArray* vertexArray, Shader* shader, glm::mat4 modelMatrix);
	};
}