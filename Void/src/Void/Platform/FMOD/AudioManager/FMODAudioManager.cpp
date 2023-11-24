#include "pch.h"
#include "FMODAudioManager.h"

void Void::Audio::FMODAudioManager::Initialize()
{
}

void Void::Audio::FMODAudioManager::Update()
{
}

void Void::Audio::FMODAudioManager::Destroy()
{
}

void Void::Audio::FMODAudioManager::LoadAudio(const char* filePath)
{
}

void Void::Audio::FMODAudioManager::LoadStream(const char* filePath)
{
}

void Void::Audio::FMODAudioManager::Load3DAudio(const char* filePath)
{
}

void Void::Audio::FMODAudioManager::PlayAudio(const char* filePath, int channelGroupIndex)
{
}

void Void::Audio::FMODAudioManager::StopAudio(unsigned int channelID)
{
}

void Void::Audio::FMODAudioManager::SetChannelVolume(unsigned int channelID, float volume)
{
}

void Void::Audio::FMODAudioManager::SetChannelPitch(unsigned int channelID, float pitch)
{
}

void Void::Audio::FMODAudioManager::SetChannelPan(unsigned int channelID, float pan)
{
}

void Void::Audio::FMODAudioManager::SetChannelGroupVolume(unsigned int groupID, float volume)
{
}

void Void::Audio::FMODAudioManager::SetChannelGroupPitch(unsigned int groupID, float volume)
{
}

void Void::Audio::FMODAudioManager::SetChannelGroupPan(unsigned int groupID, float volume)
{
}

void Void::Audio::FMODAudioManager::AddReverbToChannel(unsigned int channelID, float decay, float density, float diffusion)
{
}

void Void::Audio::FMODAudioManager::AddLowPassToChannel(unsigned int channelID, unsigned int limit)
{
}

void Void::Audio::FMODAudioManager::AddHighPassToChannel(unsigned int channelID, unsigned int limit)
{
}

void Void::Audio::FMODAudioManager::AddDistortionToChannel(unsigned int channelID, float level)
{
}

void Void::Audio::FMODAudioManager::AddChorusToChannel(unsigned int channelID, unsigned int mix, float rate, unsigned int depth)
{
}

void Void::Audio::FMODAudioManager::AddReverbToChannelGroup(unsigned int channelGroupID, float decay, float density, float diffusion)
{
}

void Void::Audio::FMODAudioManager::AddLowPassToChannelGroup(unsigned int channelGroupID, unsigned int limit)
{
}

void Void::Audio::FMODAudioManager::AddHighPassToChannelGroup(unsigned int channelGroupID, unsigned int limit)
{
}

void Void::Audio::FMODAudioManager::AddDistortionToChannelGroup(unsigned int channelGroupID, float level)
{
}

void Void::Audio::FMODAudioManager::AddChorusToChannelGroup(unsigned int channelGroupID, unsigned int mix, float rate, unsigned int depth)
{
}

void Void::Audio::FMODAudioManager::SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up)
{
}

void Void::Audio::FMODAudioManager::AddPolygon(float direct, float reverb, bool doublesided, const std::vector<glm::vec3>& vertices, const glm::vec3& position)
{
}
