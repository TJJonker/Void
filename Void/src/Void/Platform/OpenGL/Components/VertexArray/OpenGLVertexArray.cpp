#include "pch.h"
#include "OpenGLVertexArray.h"
#include <Void/Platform/OpenGL/Debugging/OpenGLDebugger.h>

namespace Void {
	OpenGLVertexArray::OpenGLVertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_ID));
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		ASSERT(vertexBuffer->GetVertexBufferLayout().GetLayoutElements().size());

		GLCall(glBindVertexArray(m_ID));
		vertexBuffer->Bind();
		
		for (const auto& element : vertexBuffer->GetVertexBufferLayout().GetLayoutElements()) {
			GLCall(glEnableVertexAttribArray(m_BufferIndex));
			glVertexAttribPointer(m_BufferIndex, element.Count, element.Type, element.Normalized, vertexBuffer->GetVertexBufferLayout().GetStride(), (const void*)element.Offset);
			m_BufferIndex++;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;

		GLCall(glBindVertexArray(m_ID));
		m_IndexBuffer->Bind();
	}

	void OpenGLVertexArray::Bind()
	{
		GLCall(glBindVertexArray(m_ID));
	}

	void OpenGLVertexArray::Unbind()
	{
		GLCall(glBindVertexArray(0));
	}
}