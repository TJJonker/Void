#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Void {
	struct Transform {
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
	};
}