#pragma once
#include "Void/Rendering/Components/IndexBuffer/IndexBuffer.h"

namespace Void::Rendering {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_ID;
		uint32_t m_Count;

	public:
		OpenGLIndexBuffer(const uint32_t* vertices, const uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
	
		virtual uint32_t GetCount() const { return m_Count; }
	};
}

