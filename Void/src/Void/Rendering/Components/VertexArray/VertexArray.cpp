#include "pch.h"
#include "VertexArray.h"
#include "Void/Rendering/Renderer.h"
#include "Void/Platform/OpenGL/Components/VertexArray/OpenGLVertexArray.h"

namespace Void {
    VertexArray* Void::VertexArray::Create()
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case RendererAPI::OpenGL:	return new OpenGLVertexArray();
        }
    }
}