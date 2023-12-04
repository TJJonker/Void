#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <glm/glm.hpp>
#include <Void/Rendering/Components/Camera/SceneCamera/SceneCamera.h>

namespace Void {
	struct CameraComponent {
		SceneCamera SceneCamera;
	};
}