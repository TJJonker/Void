#pragma once
#include "Void/Rendering/Components/VertexBuffer/VertexBuffer.h"

namespace Void::Rendering {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_ID;
		uint32_t m_Count;
		void* m_Data;

		VertexBufferLayout m_BufferLayout;

	public:
		OpenGLVertexBuffer(const void* vertices, const size_t size);
		OpenGLVertexBuffer(const size_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		 
		virtual void SetDate(const void* data, uint32_t size) override;

		void SetVertexBufferLayout(VertexBufferLayout& bufferLayout) override { m_BufferLayout = bufferLayout; }	 
		const VertexBufferLayout& GetVertexBufferLayout() const override { return m_BufferLayout; }

		uint32_t GetCount() const override { return m_Count; }
		virtual const void* GetData() const override { return m_Data; }
	};
}
