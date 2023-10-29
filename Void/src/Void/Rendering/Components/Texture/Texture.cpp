#include "pch.h"
#include "Texture.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/Texture/OpenGLTexture.h"

namespace Void {
	Texture* Texture::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI()) {
		case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
		case Renderer::API::OpenGL:	    return new OpenGLTexture(filePath);
		}
	}
}