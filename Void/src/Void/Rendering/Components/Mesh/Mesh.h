#pragma once
#include <vector>
#include <Void/Rendering/Components/VertexArray/VertexArray.h>

namespace Void::Rendering {
	struct Mesh {
		std::vector<std::unique_ptr<VertexArray>> Submeshes;
	};
}