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
		virtual const void* GetData() const = 0;

		virtual void SetDate(const void* data, uint32_t size) = 0;

		virtual void SetVertexBufferLayout(VertexBufferLayout& bufferLayout) = 0;
		virtual const VertexBufferLayout& GetVertexBufferLayout() const = 0;

		static VertexBuffer* Create(const void* vertices, size_t size);
		static VertexBuffer* Create(size_t size);
	};
}