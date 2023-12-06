#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	struct TransformComponent : public ISerializable {
		glm::vec3 Position = glm::vec3(0);
		glm::vec3 Rotation = glm::vec3(0);
		glm::vec3 Scale = glm::vec3(1);

		glm::mat4 GetTransformMatrix() const {
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);
			glm::mat4 rotationMatrix = glm::toMat4(glm::quat(Rotation));
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

			return translationMatrix * rotationMatrix * scaleMatrix;
		}

		glm::vec3 GetForwardVector() const {
			return -glm::vec3(glm::mat3(GetTransformMatrix())[2]);
		}
		glm::vec3 GetUpVector() const {
			return glm::vec3(glm::mat3(GetTransformMatrix())[1]);
		}

		void Rotate(glm::vec3 axis, float angleDegrees) {
			glm::quat additionalRotation = glm::angleAxis(glm::radians(angleDegrees), axis);
			Rotation = additionalRotation * Rotation;
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