#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Void {
	struct Transform {
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

	public:
		glm::mat4 GetTransformMatrix() const {
			glm::mat4 transform = glm::mat4(1.0f); // Identity matrix

			// Apply translation
			transform = glm::translate(transform, Position);

			// Apply rotation
			transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			// Apply scale
			transform = glm::scale(transform, Scale);
			return transform;
		}
	};
}