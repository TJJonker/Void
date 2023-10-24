#pragma once
#include <glad/glad.h>
#include <Void/Debug/Assertion.h>

namespace Void {
	struct VertexBufferLayoutElement {
		unsigned int Type;
		unsigned int Count;
		bool Normalized;
		unsigned int Offset;
	};
}