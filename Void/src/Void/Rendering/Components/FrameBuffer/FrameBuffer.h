#pragma once
#include "Void/Rendering/Components/FrameBuffer/FrameBufferConfig.h"

namespace Void::Rendering {
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Generate() = 0;
		virtual void Resize(uint16_t width, uint16_t height) = 0;

		virtual unsigned int GetRenderingID() const = 0;

		static FrameBuffer* Create(const FrameBufferConfig& config);
	};
}
