#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <glm/glm.hpp>
#include "Void/Rendering/Components/Renderer/PointLightData.h"

namespace Void {

	struct PointLightComponent : public ISerializable {
		PointLightData pointLightData{};

		nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Constant"] = pointLightData.Constant;
			json["Linear"] = pointLightData.Linear;
			json["Quadratic"] = pointLightData.Quadratic;
			json["Ambient"]["R"] = pointLightData.Ambient.x;
			json["Ambient"]["G"] = pointLightData.Ambient.y;
			json["Ambient"]["B"] = pointLightData.Ambient.z;
			json["Diffuse"]["R"] = pointLightData.Diffuse.x;
			json["Diffuse"]["G"] = pointLightData.Diffuse.y;
			json["Diffuse"]["B"] = pointLightData.Diffuse.z;
			return json;
		}

		void FromJSON(const nlohmann::json& json) override {
			pointLightData.Constant = json["Constant"];
			pointLightData.Linear = json["Linear"];
			pointLightData.Quadratic = json["Quadratic"];
			pointLightData.Ambient.x = json["Ambient"]["R"];
			pointLightData.Ambient.y = json["Ambient"]["G"];
			pointLightData.Ambient.z = json["Ambient"]["B"];

			pointLightData.Diffuse.x = json["Diffuse"]["R"];
			pointLightData.Diffuse.y = json["Diffuse"]["G"];
			pointLightData.Diffuse.z = json["Diffuse"]["B"];
		}
	};
}