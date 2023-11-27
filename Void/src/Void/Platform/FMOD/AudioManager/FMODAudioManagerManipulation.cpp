#include "pch.h"
#include "FMODAudioManager.h"
#include <fmod/fmod_errors.h>

namespace Void::Audio {
	void FMODAudioManager::SetChannelVolume(unsigned int channelID, unsigned int volume)
	{
		FMOD_RESULT result = m_ChannelsPool->GetPoolObject(channelID)->FMODChannel->setVolume((float)volume);
		VOID_ERROR("Error while setting the volume of channel: '{0}' - {1}", channelID, FMOD_ErrorString(result));
		m_ChannelsPool->GetPoolObject(channelID)->Volume = volume;
	}

	void FMODAudioManager::SetChannelPitch(unsigned int channelID, float pitch)
	{
		FMOD_RESULT result = m_ChannelsPool->GetPoolObject(channelID)->FMODChannel->setPitch(pitch);
		VOID_ERROR("Error while setting the pitch of channel: '{0}' - {1}", channelID, FMOD_ErrorString(result));
		m_ChannelsPool->GetPoolObject(channelID)->Pitch = pitch;
	}

	void FMODAudioManager::SetChannelPan(unsigned int channelID, float pan)
	{
		FMOD_RESULT result = m_ChannelsPool->GetPoolObject(channelID)->FMODChannel->setPan(pan);
		VOID_ERROR("Error while setting the pan of channel: '{0}' - {1}", channelID, FMOD_ErrorString(result));
		m_ChannelsPool->GetPoolObject(channelID)->Pan = pan;
	}

	void FMODAudioManager::SetChannelGroupVolume(unsigned int groupID, unsigned int volume)
	{
		VOID_ASSERT(groupID < m_ChannelGroups.size(), "ID out of bounds.");
		FMOD_RESULT result = m_ChannelGroups[groupID]->ChannelGroup->setVolume((float)volume);
		VOID_ERROR("Error while setting the volume of channelGroup: '{0}' - {1}", groupID, FMOD_ErrorString(result));
		m_ChannelGroups[groupID]->Volume = volume;
	}

	void FMODAudioManager::SetChannelGroupPitch(unsigned int groupID, float pitch)
	{
		VOID_ASSERT(groupID < m_ChannelGroups.size(), "ID out of bounds.");
		FMOD_RESULT result = m_ChannelGroups[groupID]->ChannelGroup->setPitch(pitch);
		VOID_ERROR("Error while setting the pitch of channelGroup: '{0}' - {1}", groupID, FMOD_ErrorString(result));
		m_ChannelGroups[groupID]->Pitch = pitch;
	}

	void FMODAudioManager::SetChannelGroupPan(unsigned int groupID, float pan)
	{
		VOID_ASSERT(groupID < m_ChannelGroups.size(), "ID out of bounds.");
		FMOD_RESULT result = m_ChannelGroups[groupID]->ChannelGroup->setPan(pan);
		VOID_ERROR("Error while setting the pan of channelGroup: '{0}' - {1}", groupID, FMOD_ErrorString(result));
		m_ChannelGroups[groupID]->Pan = pan;
	}
}