#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <glm/glm.hpp>

namespace Void {
	struct LightComponent : public ISerializable {

		float Constant = 1.0f;
		float Linear = 0.09f;
		float Quadratic = 0.032f;
		glm::vec3 Ambient = glm::vec3(0);
		glm::vec3 Diffuse = glm::vec3(0);

		nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Constant"] = Constant;
			json["Linear"] = Linear;
			json["Quadratic"] = Quadratic;

			json["Ambient"]["R"] = Ambient.x;
			json["Ambient"]["G"] = Ambient.y;
			json["Ambient"]["B"] = Ambient.z;

			json["Diffuse"]["R"] = Diffuse.x;
			json["Diffuse"]["G"] = Diffuse.y;
			json["Diffuse"]["B"] = Diffuse.z;
			return json;
		}

		void FromJSON(const nlohmann::json& json) override {
			Constant = json["Constant"];
			Linear = json["Linear"];
			Quadratic = json["Quadratic"];

			Ambient.x = json["Ambient"]["R"];
			Ambient.y = json["Ambient"]["G"];
			Ambient.z = json["Ambient"]["B"];
										 
			Diffuse.x = json["Diffuse"]["R"];
			Diffuse.y = json["Diffuse"]["G"];
			Diffuse.z = json["Diffuse"]["B"];
		}
	};
}