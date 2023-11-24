#include "pch.h"
#include "FMODAudioManager.h"

namespace Void::Audio {
	FMOD_RESULT F_CALLBACK channelFinishedCallback(FMOD_CHANNELCONTROL* channelControl, FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType, void* commandData1, void* commandData2) {
		if (callbackType == FMOD_CHANNELCONTROL_CALLBACK_END) {
			std::cout << "Channel finished playing!" << std::endl;
			// Perform any actions you need when the channel finishes playing
		}

		return FMOD_OK;
	}

	void FMODAudioManager::Initialize(unsigned int maxChannels)
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&m_System);
		VOID_ASSERT(result, "Failed to create the audio system.");

		result = m_System->init(maxChannels, FMOD_INIT_NORMAL, (void*)0);
		VOID_ASSERT(result, "Failed to initialize the audio system.");

		m_Library = new FMODAudioLibrary(m_System);

		for (unsigned int i = 0; i < maxChannels; i++)
			m_Channels.push_back(new Channel());
	}

	void FMODAudioManager::Update()
	{
		m_System->update();
	}

	void FMODAudioManager::Destroy()
	{
		m_System->release();
	}

	void FMODAudioManager::LoadAudio(const char* filePath)
	{
		m_Library->LoadAudio(filePath);
	}

	void FMODAudioManager::LoadStream(const char* filePath)
	{
		m_Library->LoadStream(filePath);
	}

	void FMODAudioManager::Load3DAudio(const char* filePath)
	{
		m_Library->Load3DAudio(filePath);
	}

	unsigned int FMODAudioManager::PlayAudio(const char* filePath, int channelGroupIndex)
	{

	}

	void Void::Audio::FMODAudioManager::StopAudio(unsigned int channelIndex)
	{
	}

	

	void Void::Audio::FMODAudioManager::AddReverbToChannel(unsigned int channelIndex, float decay, float density, float diffusion)
	{
	}

	void Void::Audio::FMODAudioManager::AddLowPassToChannel(unsigned int channelIndex, unsigned int limit)
	{
	}

	void Void::Audio::FMODAudioManager::AddHighPassToChannel(unsigned int channelIndex, unsigned int limit)
	{
	}

	void Void::Audio::FMODAudioManager::AddDistortionToChannel(unsigned int channelIndex, float level)
	{
	}

	void Void::Audio::FMODAudioManager::AddChorusToChannel(unsigned int channelIndex, unsigned int mix, float rate, unsigned int depth)
	{
	}

	void Void::Audio::FMODAudioManager::AddReverbToChannelGroup(unsigned int channelGroupIndex, float decay, float density, float diffusion)
	{
	}

	void Void::Audio::FMODAudioManager::AddLowPassToChannelGroup(unsigned int channelGroupIndex, unsigned int limit)
	{
	}

	void Void::Audio::FMODAudioManager::AddHighPassToChannelGroup(unsigned int channelGroupIndex, unsigned int limit)
	{
	}

	void Void::Audio::FMODAudioManager::AddDistortionToChannelGroup(unsigned int channelGroupIndex, float level)
	{
	}

	void Void::Audio::FMODAudioManager::AddChorusToChannelGroup(unsigned int channelGroupIndex, unsigned int mix, float rate, unsigned int depth)
	{
	}

	void Void::Audio::FMODAudioManager::SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up)
	{
	}

	void Void::Audio::FMODAudioManager::AddPolygon(float direct, float reverb, bool doublesided, const std::vector<glm::vec3>& vertices, const glm::vec3& position)
	{
	}
}