#pragma once
#include <string>

namespace Void {
	struct IntroTrigger {
		float DistanceToPlayer;
		bool Entered;
		std::string SoundPath;
	};
}