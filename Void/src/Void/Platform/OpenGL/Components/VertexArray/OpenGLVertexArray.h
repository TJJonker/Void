#pragma once
#include "Void/Rendering/Components/VertexArray/VertexArray.h"

namespace Void::Rendering {
	class OpenGLVertexArray : public VertexArray
	{
	private:
		unsigned int m_ID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		unsigned int m_BufferIndex;

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffer; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

		void Bind() override;
		void Unbind() override;

	};
}
