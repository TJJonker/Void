#include "pch.h"
#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>
#include "Void/Platform/OpenGL/Debugging/OpenGLDebugger.h"

namespace Void::Rendering {

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* vertices, const uint32_t size)
		: m_Count(size)
	{
		// Make sure the sizes match.
		ASSERT(sizeof(uint32_t) == sizeof(GLuint));

		// Generate buffer.
		GLCall(glGenBuffers(1, &m_ID));
		// Bind buffer.
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		// Fill buffer.
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), vertices, GL_STATIC_DRAW));

		m_Indices = new uint32_t[size];
		std::memcpy(m_Indices, vertices, size * sizeof(uint32_t));
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t size)
		: m_Count(size)
	{
		// Make sure the sizes match.
		ASSERT(sizeof(uint32_t) == sizeof(GLuint));

		// Generate buffer.
		GLCall(glGenBuffers(1, &m_ID));
		// Bind buffer.
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		// Fill buffer.
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		// Remove buffer.
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void OpenGLIndexBuffer::Bind() const
	{
		// Bind buffer.
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		// Unbind buffer.
	}

	void OpenGLIndexBuffer::SetData(uint32_t* indices, uint32_t size)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, indices));
	}
}
