#include "pch.h"
#include "VertexBuffer.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/VertexBuffer/OpenGLVertexBuffer.h"

namespace Void::Rendering {
    VertexBuffer* VertexBuffer::Create(const void* vertices, size_t size)
    {
        switch (Renderer::GetAPI()) {
            case Renderer::API::None:     VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case Renderer::API::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
            default: VOID_ASSERT(false, "Invalid option selected or not implemented yet."); return nullptr;
        }
    }

    VertexBuffer* VertexBuffer::Create(size_t size)
    {
        switch (Renderer::GetAPI()) {
            case Renderer::API::None:     VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case Renderer::API::OpenGL:   return new OpenGLVertexBuffer(size);
            default: VOID_ASSERT(false, "Invalid option selected or not implemented yet."); return nullptr;
        }
    }
}