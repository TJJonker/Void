#pragma once
#include "Void/Rendering/Components/VertexArray/VertexArray.h"

namespace Void::Rendering {

	class Renderer {
	public:
		enum class API {
			None, OpenGL
		};

	private:
		static API m_RendererAPI;

	public:
		virtual void Draw(const std::shared_ptr<VertexArray> vertexArray) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		static API GetAPI() { return m_RendererAPI; }
	};
}