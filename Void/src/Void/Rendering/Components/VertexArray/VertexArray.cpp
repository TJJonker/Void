#include "pch.h"
#include "VertexArray.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/VertexArray/OpenGLVertexArray.h"

namespace Void {
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI()) {
            case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case Renderer::API::OpenGL:	    return new OpenGLVertexArray();
        }
    }
}