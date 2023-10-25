#pragma once
#include <Void/Rendering/Components/VertexArray/VertexArray.h>
#include <Void/Rendering/Components/Texture/Texture.h>
#include <Void/Rendering/Components/Shader/Shader.h>

namespace Void {
	struct Submesh {
		std::shared_ptr<VertexArray> VertexArray;
		std::vector<std::shared_ptr<Texture>> Textures;
		std::shared_ptr<Shader> Shader;
	};

	struct Model {
		std::vector<std::shared_ptr<Submesh>> Submeshes;
	};
}