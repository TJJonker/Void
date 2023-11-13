#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	struct TransformComponent : public ISerializable {
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		glm::mat4 GetTransformMatrix() const {
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);
			glm::mat4 rotationMatrix = 
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * 
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * 
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

			//return scaleMatrix * rotationMatrix * translationMatrix;
			return translationMatrix * rotationMatrix * scaleMatrix;
		}

		nlohmann::ordered_json ToJSON() const override {  
			nlohmann::ordered_json json;
			json["Position"]["X"] = Position.x;
			json["Position"]["Y"] = Position.y;
			json["Position"]["Z"] = Position.z;

			json["Rotation"]["X"] = Rotation.x;
			json["Rotation"]["Y"] = Rotation.y;
			json["Rotation"]["Z"] = Rotation.z;

			json["Scale"]["X"] = Scale.x;
			json["Scale"]["Y"] = Scale.y;
			json["Scale"]["Z"] = Scale.z;

			return json;
		}

		void FromJSON(const nlohmann::json& json) override { 
			Position.x = json["Position"]["X"];
			Position.y = json["Position"]["Y"];
			Position.z = json["Position"]["Z"];

			Rotation.x = json["Rotation"]["X"];
			Rotation.y = json["Rotation"]["Y"];
			Rotation.z = json["Rotation"]["Z"];

			Scale.x = json["Scale"]["X"];
			Scale.y = json["Scale"]["Y"];
			Scale.z = json["Scale"]["Z"];
		}
	};
}