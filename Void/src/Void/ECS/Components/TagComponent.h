#pragma once
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	struct TagComponent : public ISerializable {
		std::string Tag;

		nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Tag"] = Tag;
			return json;
		}

		void FromJSON(const nlohmann::json& json) override {
			Tag = json["Tag"];
		}
	};
}