#pragma once
#include "Void/Rendering/Components/VertexBuffer/VertexBuffer.h"

namespace Void::Rendering {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_ID;
		uint32_t m_Count;

		VertexBufferLayout m_BufferLayout;

	public:
		OpenGLVertexBuffer(const void* vertices, const uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		 
		void SetVertexBufferLayout(VertexBufferLayout& bufferLayout) override { m_BufferLayout = bufferLayout; }	 
		const VertexBufferLayout& GetVertexBufferLayout() const override { return m_BufferLayout; }

		uint32_t GetCount() const override { return m_Count; }
	};
}
