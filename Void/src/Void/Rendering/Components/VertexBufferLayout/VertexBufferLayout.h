#pragma once
#include <vector>
#include <glad/glad.h>
#include "VertexBufferLayoutElement.h"

// TODO: Needs to be further abstracted... 

namespace Void {
	class VertexBufferLayout {
	private:
		std::vector<VertexBufferLayoutElement> m_Elements;
		unsigned int m_Stride;
		unsigned int m_Offset;

	public:
		VertexBufferLayout() : m_Stride(0), m_Offset(0) {}

		template<typename T>
		void Push(unsigned int count) {
			ASSERT(false);
		}

		template<>
		void Push<unsigned int>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, false, m_Offset});
			m_Offset += count;
			m_Stride += sizeof(unsigned int) * count;
		}

		template<>
		void Push<float>(unsigned int count) {
			m_Elements.push_back({ GL_FLOAT, count, false, m_Offset });
			m_Offset += count;
			m_Stride += sizeof(float) * count;
		}

		template<>
		void Push<unsigned char>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, false, m_Offset });
			m_Offset += count;
			m_Stride += sizeof(unsigned int) * count;
		}

		inline const std::vector<VertexBufferLayoutElement> GetLayoutElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }
	};
}