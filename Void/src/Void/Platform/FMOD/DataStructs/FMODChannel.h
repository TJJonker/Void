#pragma once
#include <fmod/fmod.hpp>
#include <Void/Utils/ObjectPooling/IPoolObject.h>
#include "Void/Audio/AudioManager/AudioManager.h"

namespace Void::Audio {
	struct Channel : public IPoolObject {

		const char*		Name;
		FMOD::Channel*	FMODChannel;
		unsigned int	Volume;
		float			Pitch;
		float			Pan;
		bool			IsPaused;
		FMOD::DSP*		DSPEffects[DSP_AMOUNT]{ nullptr };

		void Reset() override 
		{
			Name		= "";
			FMODChannel = nullptr;
			Volume		= 50;
			Pitch		= 1.f;
			Pan			= 0.f;
			IsPaused	= false;

			for (int i = 0; i < DSP_AMOUNT; ++i) {
				if (DSPEffects[i] != nullptr) {
					delete DSPEffects[i];
					DSPEffects[i] = nullptr; 
				}
			}
		}
	};
}