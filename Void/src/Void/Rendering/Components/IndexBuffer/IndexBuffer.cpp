#include "pch.h"
#include "IndexBuffer.h"
#include "Void/Rendering/Renderer.h"
#include "Void/Platform/OpenGL/Components/IndexBuffer/OpenGLIndexBuffer.h"

namespace Void {

	IndexBuffer* Void::IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
			case Renderer::API::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}
	}
}
