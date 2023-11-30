#include "pch.h"
#include "AudioManager.h"
#include "Void/Platform/FMOD/AudioManager/FMODAudioManager.h"

namespace Void::Audio {
	AudioManager* AudioManager::m_Instance = nullptr;

	AudioManager* AudioManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new FMODAudioManager();
		return m_Instance;
	}
}