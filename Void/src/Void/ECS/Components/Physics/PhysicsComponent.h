#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <Quantum/Quantum.h>

namespace Void {
	struct PhysicsComponent : public ISerializable {

		glm::vec3 Force = glm::vec3(0);
		float Mass = 1;

		virtual nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Mass"] = Mass;
			return json;
		}

		virtual void FromJSON(const nlohmann::json& json) override {
			Mass = json["Mass"];
		}

	};
}