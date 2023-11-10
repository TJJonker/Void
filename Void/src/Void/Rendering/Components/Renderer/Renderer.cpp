#include "pch.h"
#include "Renderer.h"
#include "Void/Platform/OpenGL/Components/Renderer/OpenGLRenderer.h"
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"

namespace Void::Rendering {
	Renderer::API Renderer::m_RendererAPI = Renderer::API::OpenGL;
	Renderer* RenderingCommands::m_Renderer = new OpenGLRenderer();
}