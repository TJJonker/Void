#pragma once
#include <fmod/fmod.hpp>
#include "Void/Audio/AudioManager/AudioManager.h"

namespace Void::Audio {
	struct ChannelGroup {

		FMOD::ChannelGroup*	Group = nullptr;
		unsigned int		Volume = 100;
		float				Pitch = 1.f;
		float				Pan = 0.f;
		FMOD::DSP*			DSPEffects[DSP_AMOUNT]{ nullptr };
	};
}