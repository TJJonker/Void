#include "pch.h"
#include "FMODAudioManager.h"

namespace Void::Audio {
#pragma region DSP Channels
	void FMODAudioManager::AddReverbToChannel(unsigned int channelIndex, float decay, float density, float diffusion)
	{
		FMOD::DSP* reverb = CreateReverbDSP(decay, density, diffusion);
		m_ChannelsPool->GetPoolObject(channelIndex)->DSPEffects[DSP_REVERB_INDEX] = reverb;
		m_ChannelsPool->GetPoolObject(channelIndex)->FMODChannel->addDSP(DSP_REVERB_INDEX, reverb);
	}

	void FMODAudioManager::AddLowPassToChannel(unsigned int channelIndex, unsigned int cutoff)
	{
		FMOD::DSP* reverb = CreateLowPassDSP(cutoff);
		m_ChannelsPool->GetPoolObject(channelIndex)->DSPEffects[DSP_LOWPASS_INDEX] = reverb;
		m_ChannelsPool->GetPoolObject(channelIndex)->FMODChannel->addDSP(DSP_LOWPASS_INDEX, reverb);
	}

	void FMODAudioManager::AddHighPassToChannel(unsigned int channelIndex, unsigned int cutoff)
	{
		FMOD::DSP* highPass = CreateHighPassDSP(cutoff);
		m_ChannelsPool->GetPoolObject(channelIndex)->DSPEffects[DSP_HIGHPASS_INDEX] = highPass;
		m_ChannelsPool->GetPoolObject(channelIndex)->FMODChannel->addDSP(DSP_HIGHPASS_INDEX, highPass);
	}

	void FMODAudioManager::AddDistortionToChannel(unsigned int channelIndex, float level)
	{
		FMOD::DSP* distortion = CreateDistortionDSP(level);
		m_ChannelsPool->GetPoolObject(channelIndex)->DSPEffects[DSP_DISTORTION_INDEX] = distortion;
		m_ChannelsPool->GetPoolObject(channelIndex)->FMODChannel->addDSP(DSP_DISTORTION_INDEX, distortion);
	}

	void FMODAudioManager::AddChorusToChannel(unsigned int channelIndex, unsigned int mix, float rate, unsigned int depth)
	{
		FMOD::DSP* chorus = CreateChorusDSP(mix, rate, depth);
		m_ChannelsPool->GetPoolObject(channelIndex)->DSPEffects[DSP_CHORUS_INDEX] = chorus;
		m_ChannelsPool->GetPoolObject(channelIndex)->FMODChannel->addDSP(DSP_CHORUS_INDEX, chorus);
	}
#pragma endregion

#pragma region DSP ChannelGroups

	void FMODAudioManager::AddReverbToChannelGroup(unsigned int channelGroupIndex, float decay, float density, float diffusion)
	{
		VOID_ASSERT(channelGroupIndex < m_ChannelGroups.size(), "Index is out of bounds.");
		FMOD::DSP* reverb = CreateReverbDSP(decay, density, diffusion);
		m_ChannelGroups[channelGroupIndex]->DSPEffects[DSP_REVERB_INDEX] = reverb;
		m_ChannelGroups[channelGroupIndex]->ChannelGroup->addDSP(DSP_REVERB_INDEX, reverb);
	}

	void FMODAudioManager::AddLowPassToChannelGroup(unsigned int channelGroupIndex, unsigned int cutoff)
	{
		VOID_ASSERT(channelGroupIndex < m_ChannelGroups.size(), "Index is out of bounds.");
		FMOD::DSP* lowPass = CreateLowPassDSP(cutoff);
		m_ChannelGroups[channelGroupIndex]->DSPEffects[DSP_LOWPASS_INDEX] = lowPass;
		m_ChannelGroups[channelGroupIndex]->ChannelGroup->addDSP(DSP_LOWPASS_INDEX, lowPass);
	}

	void FMODAudioManager::AddHighPassToChannelGroup(unsigned int channelGroupIndex, unsigned int cutoff)
	{
		VOID_ASSERT(channelGroupIndex < m_ChannelGroups.size(), "Index is out of bounds.");
		FMOD::DSP* highPass = CreateHighPassDSP(cutoff);
		m_ChannelGroups[channelGroupIndex]->DSPEffects[DSP_HIGHPASS_INDEX] = highPass;
		m_ChannelGroups[channelGroupIndex]->ChannelGroup->addDSP(DSP_HIGHPASS_INDEX, highPass);
	}

	void FMODAudioManager::AddDistortionToChannelGroup(unsigned int channelGroupIndex, float level)
	{
		VOID_ASSERT(channelGroupIndex < m_ChannelGroups.size(), "Index is out of bounds.");
		FMOD::DSP* distortion = CreateDistortionDSP(level);
		m_ChannelGroups[channelGroupIndex]->DSPEffects[DSP_DISTORTION_INDEX] = distortion;
		m_ChannelGroups[channelGroupIndex]->ChannelGroup->addDSP(DSP_DISTORTION_INDEX, distortion);
	}

	void FMODAudioManager::AddChorusToChannelGroup(unsigned int channelGroupIndex, unsigned int mix, float rate, unsigned int depth)
	{
		VOID_ASSERT(channelGroupIndex < m_ChannelGroups.size(), "Index is out of bounds.");
		FMOD::DSP* chorus = CreateChorusDSP(mix, rate, depth);
		m_ChannelGroups[channelGroupIndex]->DSPEffects[DSP_CHORUS_INDEX] = chorus;
		m_ChannelGroups[channelGroupIndex]->ChannelGroup->addDSP(DSP_CHORUS_INDEX, chorus);
	}

#pragma endregion

#pragma region DSP Creation
	FMOD::DSP* FMODAudioManager::CreateReverbDSP(float decay, float density, float diffusion)
	{
		FMOD::DSP* reverb;
		FMOD_RESULT result;

		result = m_System->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &reverb);
		VOID_ASSERT(result, "Failed to create the reverb dsp.");

		result = reverb->setParameterFloat(FMOD_DSP_SFXREVERB_DECAYTIME, decay);
		VOID_ASSERT(result, "Failed to set the decay in the reverb dsp.");
		result = reverb->setParameterFloat(FMOD_DSP_SFXREVERB_DENSITY, density);
		VOID_ASSERT(result, "Failed to set the density in the reverb dsp.");
		result = reverb->setParameterFloat(FMOD_DSP_SFXREVERB_DIFFUSION, diffusion);
		VOID_ASSERT(result, "Failed to set the diffusion in the reverb dsp.");

		return reverb;
	}

	FMOD::DSP* FMODAudioManager::CreateLowPassDSP(unsigned int cutoff)
	{
		FMOD::DSP* lowPass;
		FMOD_RESULT result;

		result = m_System->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &lowPass);
		VOID_ASSERT(result, "Failed to create the lowPass dsp.");

		result = lowPass->setParameterInt(FMOD_DSP_LOWPASS_CUTOFF, cutoff);
		VOID_ASSERT(result, "Failed to set the cutoff in the lowPass dsp.");

		return lowPass;
	}

	FMOD::DSP* FMODAudioManager::CreateHighPassDSP(unsigned int cutoff)
	{
		FMOD::DSP* highPass;
		FMOD_RESULT result;

		result = m_System->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &highPass);
		VOID_ASSERT(result, "Failed to create the highPass dsp.");

		result = highPass->setParameterInt(FMOD_DSP_HIGHPASS_CUTOFF, cutoff);
		VOID_ASSERT(result, "Failed to set the cutoff in the highPass dsp.");

		return highPass;
	}

	FMOD::DSP* FMODAudioManager::CreateDistortionDSP(float level)
	{
		FMOD::DSP* distortion;
		FMOD_RESULT result;

		result = m_System->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &distortion);
		VOID_ASSERT(result, "Failed to create the distortion dsp.");

		result = distortion->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, level);
		VOID_ASSERT(result, "Failed to set the decay in the distortion dsp.");

		return distortion;
	}

	FMOD::DSP* FMODAudioManager::CreateChorusDSP(unsigned int mix, float rate, unsigned int depth)
	{
		FMOD::DSP* chorus;
		FMOD_RESULT result;

		result = m_System->createDSPByType(FMOD_DSP_TYPE_CHORUS, &chorus);
		VOID_ASSERT(result, "Failed to create the chorus dsp.");

		result = chorus->setParameterInt(FMOD_DSP_CHORUS_MIX, mix);
		VOID_ASSERT(result, "Failed to set the mix in the chorus dsp.");
		result = chorus->setParameterFloat(FMOD_DSP_CHORUS_RATE, rate);
		VOID_ASSERT(result, "Failed to set the rate in the chorus dsp.");
		result = chorus->setParameterInt(FMOD_DSP_CHORUS_DEPTH, depth);
		VOID_ASSERT(result, "Failed to set the depth in the chorus dsp.");

		return chorus;
	}

#pragma endregion
}