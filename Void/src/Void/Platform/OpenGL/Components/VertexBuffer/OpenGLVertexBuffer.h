#pragma once
#include "Void/Rendering/Components/VertexBuffer/VertexBuffer.h"

namespace Void {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_ID;
		uint32_t m_Count;

	public:
		OpenGLVertexBuffer(const float* vertices, const uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; }
	};
}
