#include "pch.h"
#include "glad/glad.h"
#include "OpenGLVertexBuffer.h"
#include "Void/Platform/OpenGL/Debugging/OpenGLDebugger.h"

namespace Void::Rendering {
    
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, const size_t size)
        : m_Size((uint32_t)size), m_Data(nullptr)
    {
        GLCall(glGenBuffers(1, &m_ID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));

        m_Data = new char[size];
        std::memcpy(m_Data, vertices, size);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const size_t size)
        : m_Size((uint32_t)size), m_Data(nullptr)
    {
        GLCall(glGenBuffers(1, &m_ID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
    }

    void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
    {
        tempData = data;
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        GLCall(glDeleteBuffers(1, &m_ID));
    }

    void OpenGLVertexBuffer::Bind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}