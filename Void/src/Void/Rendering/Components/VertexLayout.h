#pragma once
#include <glm/glm.hpp>

namespace Void {
	struct VertexLayout {
		glm::vec3 Position;
		glm::vec3 Normals;
		glm::vec2 TextureCoords;
	};
}