#pragma once
#include "glm/glm.hpp"
#include "Void/Utils/Parser/Serializable.h"

namespace Void {
	struct TransformComponent : public Serializable {
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		TransformComponent() {
			AddMetaTitle("TransformComponent");
			AddMetaData({ "Position", MetaData::DataType::VEC3, &Position });
			AddMetaData({ "Rotation", MetaData::DataType::VEC3, &Rotation });
			AddMetaData({ "Scale", MetaData::DataType::VEC3, &Scale });
		}
	};
}