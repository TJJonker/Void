#include "pch.h"
#include "FMODAudioManager.h"

namespace Void::Audio {
	void FMODAudioManager::SetChannelVolume(unsigned int channelID, float volume)
	{
		FMOD_RESULT result = channel->FMODChannel->setPitch(channel->Pitch);
	}

	void FMODAudioManager::SetChannelPitch(unsigned int channelID, float pitch)
	{
	}

	void FMODAudioManager::SetChannelPan(unsigned int channelID, float pan)
	{
	}

	void FMODAudioManager::SetChannelGroupVolume(unsigned int groupID, float volume)
	{
	}

	void FMODAudioManager::SetChannelGroupPitch(unsigned int groupID, float volume)
	{
	}

	void FMODAudioManager::SetChannelGroupPan(unsigned int groupID, float volume)
	{
	}
}