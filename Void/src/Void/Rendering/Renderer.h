#pragma once

namespace Void {
	enum class RendererAPI {
		None, OpenGL
	};

	class Renderer {
	private:
		static RendererAPI m_RendererAPI;

	public:
		inline static RendererAPI GetAPI() { return m_RendererAPI; }
	};
}