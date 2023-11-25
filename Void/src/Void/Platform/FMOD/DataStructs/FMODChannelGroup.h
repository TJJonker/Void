#pragma once
#include <fmod/fmod.hpp>
#include "Void/Audio/AudioManager/AudioManager.h"

namespace Void::Audio {
	struct ChannelGroup {
		FMOD::ChannelGroup*	ChannelGroup;
		unsigned int		Volume;
		float				Pitch;
		float				Pan;
		FMOD::DSP*			DSPEffects[DSP_AMOUNT]{ nullptr };
	};
}