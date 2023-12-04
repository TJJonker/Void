#pragma once
#include "Void/Rendering/Components/IndexBuffer/IndexBuffer.h"

namespace Void::Rendering {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_ID;
		uint32_t m_Count;
		uint32_t* m_Indices;

	public:
		OpenGLIndexBuffer(const uint32_t* vertices, const uint32_t size);
		OpenGLIndexBuffer(const uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void SetData(uint32_t* indices, uint32_t size) override;	
		
		virtual uint32_t GetCount() const override{ return m_Count; }
		virtual const uint32_t* GetIndices() const { return m_Indices; }
	};
}

