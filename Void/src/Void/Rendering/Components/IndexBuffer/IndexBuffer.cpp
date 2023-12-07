#include "pch.h"
#include "IndexBuffer.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/IndexBuffer/OpenGLIndexBuffer.h"

namespace Void::Rendering {

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
			case Renderer::API::OpenGL:	return new OpenGLIndexBuffer(indices, size);
			default: VOID_ASSERT(false, "Invalid option selected or not implemented yet."); return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
			case Renderer::API::OpenGL:	return new OpenGLIndexBuffer(size);
			default: VOID_ASSERT(false, "Invalid option selected or not implemented yet."); return nullptr;
		}
	}
}
