#pragma once
#include "Void/Rendering/Components/VertexBuffer/VertexBuffer.h"
#include <Void/Rendering/Components/IndexBuffer/IndexBuffer.h>

namespace Void {
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static VertexArray* Create();
	};
}