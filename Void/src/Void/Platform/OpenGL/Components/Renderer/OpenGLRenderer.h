#pragma once
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include <Void/Rendering/Components/Shader/Shader.h>

namespace Void::Rendering {
	class OpenGLRenderer : public Renderer
	{
		void Draw(const std::shared_ptr<VertexArray> vertexArray) override;
		void Clear() override;
		void SetClearColor(const glm::vec4& color) override;
	};
}
