#include "pch.h"
#include "FrameBuffer.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/FrameBuffer/OpenGLFrameBuffer.h"

namespace Void::Rendering {
	FrameBuffer* FrameBuffer::Create(const FrameBufferConfig& config)
	{
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
			case Renderer::API::OpenGL:	    return new OpenGLFrameBuffer(config);
		}
	}
}