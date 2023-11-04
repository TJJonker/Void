#pragma once
#include "Void/Rendering/Components/Model/Model.h"
#include <memory>

namespace Void {
	struct RenderingComponent {
		std::vector<std::shared_ptr<Rendering::Submesh>> Submeshes;
	};
}