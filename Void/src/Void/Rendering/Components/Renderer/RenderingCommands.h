#pragma once
#include <glm/glm.hpp>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include "Renderer.h"

namespace Void {
	class RenderingCommands {
	private:
		static Renderer* m_Renderer;

	public:
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void Draw(const std::shared_ptr<VertexArray> vertexArray);
	};
}