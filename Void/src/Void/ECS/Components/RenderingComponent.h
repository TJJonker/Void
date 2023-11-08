#pragma once
#include "Void/Rendering/Components/Model/Submesh.h"

namespace Void {
	struct RenderingComponent : public ISerializable {
		std::vector<Rendering::Submesh> Submeshes;

		nlohmann::json ToJSON() const override {
			nlohmann::json json;
			for (Rendering::Submesh submesh : Submeshes)
				json.push_back(submesh.ToJSON());			
			return json;
		}

		void FromJSON(nlohmann::json) override {

		}
	};
}