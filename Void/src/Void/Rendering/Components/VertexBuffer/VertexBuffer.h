#pragma once
#include <Void/Rendering/Components/VertexBufferLayout/VertexBufferLayout.h>

namespace Void::Rendering {
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0; 
		virtual const char* GetData() const = 0;

		virtual void SetVertexBufferLayout(VertexBufferLayout& bufferLayout) = 0;
		virtual const VertexBufferLayout& GetVertexBufferLayout() const = 0;

		static VertexBuffer* Create(const void* vertices, size_t size);
	};
}