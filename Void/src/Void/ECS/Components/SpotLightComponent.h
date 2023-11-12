#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <glm/glm.hpp>

namespace Void {
	struct SpotLightComponent : public ISerializable {

		glm::vec3 Direction = glm::normalize(glm::vec3(0.0, -1.0, 0.0));
		float CutOff = 15.0f;
		float OuterCutOff = 30.0f;
		float Constant = 1.0f;
		float Linear = 0.09f;
		float Quadratic = 0.032f;
		glm::vec3 Ambient = glm::vec3(0.2, 0.2, 0.2);
		glm::vec3 Diffuse = glm::vec3(0.8, 0.8, 0.6);
		glm::vec3 Specular = glm::vec3(1.0, 1.0, 1.0);

		nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Direction"]["X"] = Direction.x;
			json["Direction"]["Y"] = Direction.y;
			json["Direction"]["Z"] = Direction.z;

			json["CutOff"] = CutOff;
			json["OuterCutOff"] = OuterCutOff;
			json["Constant"] = Constant;
			json["Linear"] = Linear;
			json["Quadratic"] = Quadratic;

			json["Ambient"]["R"] = Ambient.x;
			json["Ambient"]["G"] = Ambient.y;
			json["Ambient"]["B"] = Ambient.z;

			json["Diffuse"]["R"] = Diffuse.x;
			json["Diffuse"]["G"] = Diffuse.y;
			json["Diffuse"]["B"] = Diffuse.z;

			json["Specular"]["R"] = Specular.x;
			json["Specular"]["G"] = Specular.y;
			json["Specular"]["B"] = Specular.z;
			return json;
		}

		void FromJSON(const nlohmann::json& json) override {
			Direction.x = json["Direction"]["X"];
			Direction.y = json["Direction"]["Y"];
			Direction.z = json["Direction"]["Z"];

			CutOff = json["CutOff"];
			OuterCutOff = json["OuterCutOff"];
			Constant = json["Constant"];
			Linear = json["Linear"];
			Quadratic = json["Quadratic"];

			Ambient.x = json["Ambient"]["R"];
			Ambient.y = json["Ambient"]["G"];
			Ambient.z = json["Ambient"]["B"];

			Diffuse.x = json["Diffuse"]["R"];
			Diffuse.y = json["Diffuse"]["G"];
			Diffuse.z = json["Diffuse"]["B"];

			Specular.x = json["Specular"]["R"];
			Specular.y = json["Specular"]["G"];
			Specular.z = json["Specular"]["B"];
		}
	};
}