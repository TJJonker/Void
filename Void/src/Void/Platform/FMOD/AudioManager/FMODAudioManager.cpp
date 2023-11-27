#include "pch.h"
#include "FMODAudioManager.h"
#include "Void/Platform/FMOD/Utils/FMODUtils.h"

namespace Void::Audio {
	FMODAudioManager::FMODAudioManager()
	{
		Initialize(100);
	}

	void FMODAudioManager::Initialize(unsigned int maxChannels)
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&m_System);
		VOID_ASSERT(result == FMOD_OK, "Failed to create the audio system.");

		result = m_System->init(maxChannels, FMOD_INIT_NORMAL, (void*)0);
		VOID_ASSERT(result == FMOD_OK, "Failed to initialize the audio system.");

		m_Library = new FMODAudioLibrary(m_System);
		m_ChannelsPool = new Pool<Channel>(maxChannels);

		{
			ChannelGroup* group = new ChannelGroup();
			m_ChannelGroups.push_back(group); // Master
			m_System->createChannelGroup("Master", &group->Group);
		}

		{
			ChannelGroup* group = new ChannelGroup();
			m_ChannelGroups.push_back(group); // Music
			m_System->createChannelGroup("Music", &group->Group);
		}

		{
			ChannelGroup* group = new ChannelGroup();
			m_ChannelGroups.push_back(group); // SFX
			m_System->createChannelGroup("SFX", &group->Group);
		}
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
		FMOD::Sound* sound = m_Library->GetSound(filePath);
		unsigned int channelIndex = m_ChannelsPool->Get();
		Channel* channel = m_ChannelsPool->GetPoolObject(channelIndex);
		m_System->playSound(sound, m_ChannelGroups[channelGroupIndex]->Group, false, &channel->FMODChannel);
		return channelIndex;
	}

	void FMODAudioManager::StopAudio(unsigned int channelIndex)
	{
		Channel* channel = m_ChannelsPool->GetPoolObject(channelIndex);
		channel->FMODChannel->stop();
		m_ChannelsPool->Release(channel);
	}

	void FMODAudioManager::SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up)
	{
		FMOD_RESULT result;
		FMOD_VECTOR fpos = ToFMOD(position);
		FMOD_VECTOR fvel = ToFMOD(velocity);
		FMOD_VECTOR ffwd = ToFMOD(forward);
		FMOD_VECTOR fup  = ToFMOD(up);

		result = m_System->set3DListenerAttributes(0, &fpos, &fvel, &ffwd, &fup);
		VOID_ASSERT(result == FMOD_OK, "Error while setting 3D listener attribute.");
	}

	void FMODAudioManager::AddPolygon(float direct, float reverb, bool doublesided, const std::vector<glm::vec3>& vertices, const glm::vec3& position)
	{

	}

	bool FMODAudioManager::IsValid(unsigned int channelID)
	{
		return m_ChannelsPool->GetPoolObject(channelID)->FMODChannel;
	}

	void FMODAudioManager::SetChannelAttributes(unsigned int channelID, const glm::vec3& position, const glm::vec3 velocity)
	{
		FMOD_RESULT result;
		FMOD_VECTOR fpos = ToFMOD(position);
		FMOD_VECTOR fvel = ToFMOD(velocity);
		result = m_ChannelsPool->GetPoolObject(channelID)->FMODChannel->set3DAttributes(&fpos, &fvel);
		VOID_ASSERT(result == FMOD_OK, "Error while setting 3D attribute.");
	}
}