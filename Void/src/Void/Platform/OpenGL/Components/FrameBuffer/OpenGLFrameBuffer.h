#pragma once
#include "Void/Rendering/Components/FrameBuffer/FrameBuffer.h"

namespace Void::Rendering {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	private:
		unsigned int m_ID = 0;
		unsigned int m_TextureID = 0;
		FrameBufferConfig m_Config;

	public:
		OpenGLFrameBuffer(const FrameBufferConfig& config);
		virtual ~OpenGLFrameBuffer();

		void Bind() override;
		void UnBind() override;

		void Generate() override;
		void Resize(uint16_t width, uint16_t height) override;
	};
}
