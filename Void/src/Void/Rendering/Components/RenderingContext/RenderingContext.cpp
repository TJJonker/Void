#include "pch.h"
#include "RenderingContext.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/RenderingContext/OpenGLRenderingContext.h"

namespace Void::Rendering {
    RenderingContext* RenderingContext::Create()
    {
        switch (Renderer::GetAPI()) {
            case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case Renderer::API::OpenGL:	    return new OpenGLRenderingContext();
            default: VOID_ASSERT(false, "Invalid option selected or not implemented yet."); return nullptr;
        }
    }
}