#pragma once
#include "Void/Rendering/Components/Model/Model.h"

namespace Void {
	struct RenderingComponent {
		std::vector<std::shared_ptr<Rendering::Submesh>> Submeshes;
	};
}