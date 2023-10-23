#pragma once

namespace Void {
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static VertexBuffer* Create(const float* vertices, uint32_t size);
	};
}