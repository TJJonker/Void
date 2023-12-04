#include "pch.h"
#include "Renderer.h"
#include "Void/Platform/OpenGL/Components/Renderer/OpenGLRenderer.h"
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"

namespace Void::Rendering {
	Renderer::API Renderer::m_RendererAPI = Renderer::API::OpenGL;
	Renderer* RenderingCommands::m_Renderer = new OpenGLRenderer();

	struct VertexLayout {
		glm::vec3 Position;
		glm::vec2 TextureCoord;
		unsigned int TextureIndex;
	};

	struct RendererData {
		static const uint32_t MaxTriangles = 20000;
		static const uint32_t MaxIndices = MaxTriangles * 3;
		static const uint32_t MaxTextureSlots = 32;

		VertexArray* BatchVertexArray;
		VertexBuffer* BatchVertexBuffer;
		Shader* BatchShader;

		uint32_t IndexCount;
		VertexLayout* VertexLayoutBufferBase = nullptr;
		VertexLayout* VertexLayoutBufferPtr = nullptr;

		std::array<Texture*, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotsIndex;

		glm::vec4 TriangleVertexPositions;
	};

	static RendererData m_RendererData;
}