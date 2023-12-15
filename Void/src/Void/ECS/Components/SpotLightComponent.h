#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <glm/glm.hpp>
#include "Void/Rendering/Components/Renderer/SpotLightData.h"

namespace Void {
	struct SpotLightComponent : public ISerializable {

		SpotLightData SpotLightData;

		nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Direction"]["X"] = SpotLightData.Direction.x;
			json["Direction"]["Y"] = SpotLightData.Direction.y;
			json["Direction"]["Z"] = SpotLightData.Direction.z;

			json["CutOff"] = SpotLightData.CutOff;
			json["OuterCutOff"] = SpotLightData.OuterCutOff;
			json["Constant"] = SpotLightData.Constant;
			json["Linear"] = SpotLightData.Linear;
			json["Quadratic"] = SpotLightData.Quadratic;

			json["Ambient"]["R"] = SpotLightData.Ambient.x;
			json["Ambient"]["G"] = SpotLightData.Ambient.y;
			json["Ambient"]["B"] = SpotLightData.Ambient.z;

			json["Diffuse"]["R"] = SpotLightData.Diffuse.x;
			json["Diffuse"]["G"] = SpotLightData.Diffuse.y;
			json["Diffuse"]["B"] = SpotLightData.Diffuse.z;
			return json;
		}

		void FromJSON(const nlohmann::json& json) override {
			SpotLightData.Direction.x = json["Direction"]["X"];
			SpotLightData.Direction.y = json["Direction"]["Y"];
			SpotLightData.Direction.z = json["Direction"]["Z"];

			SpotLightData.CutOff = json["CutOff"];
			SpotLightData.OuterCutOff = json["OuterCutOff"];
			SpotLightData.Constant = json["Constant"];
			SpotLightData.Linear = json["Linear"];
			SpotLightData.Quadratic = json["Quadratic"];

			SpotLightData.Ambient.x = json["Ambient"]["R"];
			SpotLightData.Ambient.y = json["Ambient"]["G"];
			SpotLightData.Ambient.z = json["Ambient"]["B"];

			SpotLightData.Diffuse.x = json["Diffuse"]["R"];
			SpotLightData.Diffuse.y = json["Diffuse"]["G"];
			SpotLightData.Diffuse.z = json["Diffuse"]["B"];
		}
	};
}