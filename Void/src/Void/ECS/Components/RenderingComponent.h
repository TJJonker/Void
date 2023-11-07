#pragma once
#include "Void/Rendering/Components/Model/Model.h"
#include "Void/Utils/Parser/Serializable.h"

namespace Void {
	struct RenderingComponent : public Serializable {
		std::vector<std::shared_ptr<Rendering::Submesh>> Submeshes;
	};
}