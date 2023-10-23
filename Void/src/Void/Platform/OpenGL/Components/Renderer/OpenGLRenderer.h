#pragma once
#include "Void/Rendering/Renderer.h"

namespace Void {
	class OpenGLRenderer : public Renderer
	{
		void Draw(const std::shared_ptr<VertexArray> vertexArray) override;
		void Clear() override;
		void SetClearColor() override;
	};
}
