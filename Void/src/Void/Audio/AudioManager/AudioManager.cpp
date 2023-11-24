#include "pch.h"
#include "AudioManager.h"
#include "Void/Platform/FMOD/AudioManager/FMODAudioManager.h"

namespace Void::Audio {
	AudioManager* AudioManager::Create()
	{
		return new FMODAudioManager();
	}
}