#include "pch.h"
#include "VertexBuffer.h"
#include "Void/Rendering/Renderer.h"
#include "Void/Platform/OpenGL/Components/VertexBuffer/OpenGLVertexBuffer.h"

namespace Void {
    VertexBuffer* VertexBuffer::Create(const float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:     VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
        }
    }
}