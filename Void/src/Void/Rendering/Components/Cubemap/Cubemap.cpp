#include "pch.h"
#include "Cubemap.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/Cubemap/OpenGLCubemap.h"

namespace Void::Rendering {
	Cubemap* Cubemap::Create(const std::vector<std::string>& textures)
	{
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
			case Renderer::API::OpenGL:	    return new OpenGLCubemap(textures);
			default: VOID_ASSERT(false, "Invalid option selected or not implemented yet."); return nullptr;
		}
	}
}