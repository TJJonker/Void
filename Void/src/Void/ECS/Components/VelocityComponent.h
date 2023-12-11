#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include "glm/glm.hpp"
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	struct VelocityComponent : public ISerializable {
		glm::vec3 Velocity;

		virtual nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Velocity"]["X"] = Velocity.x;
			json["Velocity"]["Y"] = Velocity.y;
			json["Velocity"]["Z"] = Velocity.z;
			return json;
		}

		virtual void FromJSON(const nlohmann::json& json) override {
			Velocity.x = json["Velocity"]["X"];
			Velocity.y = json["Velocity"]["Y"];
			Velocity.z = json["Velocity"]["Z"];
		}
	};
}
