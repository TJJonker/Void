#pragma once
#include "Void.h"

namespace Nebula::Events {
	struct EntitySelected {
		Void::Entity* entity;
	};
}