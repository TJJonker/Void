#include "pch.h"
#include "VertexBuffer.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/VertexBuffer/OpenGLVertexBuffer.h"

namespace Void::Rendering {
    VertexBuffer* VertexBuffer::Create(const void* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI()) {
            case Renderer::API::None:     VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case Renderer::API::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
        }
    }
}