#pragma once

namespace Void::Rendering {
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
		virtual const uint32_t* GetIndices() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
		static IndexBuffer* Create(uint32_t size);

		virtual void SetData(uint32_t* indices, uint32_t size) = 0;
	};
}

