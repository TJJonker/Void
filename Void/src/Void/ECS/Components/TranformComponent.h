#pragma once
#include "glm/glm.hpp"
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	struct TransformComponent : public ISerializable {
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		nlohmann::json ToJSON() const override {  
			nlohmann::json json; 
			json["Position"]["X"] = Position.x;
			json["Position"]["Y"] = Position.y;
			json["Position"]["Z"] = Position.z;

			json["Rotation"]["X"] = Rotation.x;
			json["Rotation"]["Y"] = Rotation.y;
			json["Rotation"]["Z"] = Rotation.z;

			json["Scale"]["X"] = Scale.x;
			json["Scale"]["Y"] = Scale.y;
			json["Scale"]["Z"] = Scale.z;

			nlohmann::json jsonObject;
			jsonObject["TransformComponent"] = json;
			return jsonObject;
		}

		void FromJSON(nlohmann::json) override { 
			
		}
	};
}