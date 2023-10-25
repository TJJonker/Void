#include "pch.h"
#include "OpenGLVertexArray.h"
#include <Void/Platform/OpenGL/Debugging/OpenGLDebugger.h>

namespace Void {
	OpenGLVertexArray::OpenGLVertexArray()
		:m_BufferIndex(0)
	{
		GLCall(glGenVertexArrays(1, &m_ID));
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)	
	{
		VOID_CORE_ASSERT(vertexBuffer->GetVertexBufferLayout().GetLayoutElements().size(), "VertexBuffer is empty.");

		GLCall(glBindVertexArray(m_ID));
		vertexBuffer->Bind();
		
		for (const auto& element : vertexBuffer->GetVertexBufferLayout().GetLayoutElements()) {
			GLCall(glEnableVertexAttribArray(m_BufferIndex));
			GLCall(glVertexAttribPointer(m_BufferIndex, element.Count, GL_FLOAT, element.Normalized, vertexBuffer->GetVertexBufferLayout().GetStride(), (const void*)element.Offset));
			m_BufferIndex++;
		}

		m_VertexBuffer.push_back(vertexBuffer);
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