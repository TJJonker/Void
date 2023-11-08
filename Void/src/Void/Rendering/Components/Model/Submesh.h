#pragma once
#include "Void/Utils/Parser/ISerializable.h"

namespace Void::Rendering {
	struct Submesh : public ISerializable {
		std::string Model;
		std::vector<std::string> Textures;
		std::string Shader;

		nlohmann::json ToJSON() const override {
			nlohmann::json json;

			json["Model"] = Model;

			for (const std::string& texture : Textures)
				json["Texture"].push_back(texture);

			json["Shader"] = Shader;

			return json;
		}

		void FromJSON(nlohmann::json) override {

		}
	};
}