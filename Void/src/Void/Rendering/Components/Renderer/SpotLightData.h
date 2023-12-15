#pragma once
#include <glm/glm.hpp>

struct SpotLightData {
	glm::vec3 Position = glm::vec3(0); 
	glm::vec3 Direction = normalize(glm::vec3(0.0, -1.0, 0.0));

	float CutOff = (float)glm::radians(15.0);
	float OuterCutOff = (float)glm::radians(30.0);
	float Constant = 1.0f;
	float Linear = 0.09f;
	float Quadratic = 0.032f;

	glm::vec3 Ambient = glm::vec3(0.2, 0.2, 0.2);
	glm::vec3 Diffuse = glm::vec3(0.8, 0.8, 0.6);
};