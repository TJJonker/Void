#pragma once
#include "Void/Audio/AudioManager/AudioManager.h"

namespace Void::Audio {
	class FMODAudioManager : public AudioManager
	{
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Destroy() override;

		virtual void LoadAudio(const char* filePath) override;
		virtual void LoadStream(const char* filePath) override;
		virtual void Load3DAudio(const char* filePath) override;

		virtual void PlayAudio(const char* filePath, int channelGroupIndex) override;
		virtual void StopAudio(unsigned int channelID) override;

		virtual void SetChannelVolume(unsigned int channelID, float volume) override;
		virtual void SetChannelPitch(unsigned int channelID, float pitch) override;
		virtual void SetChannelPan(unsigned int channelID, float pan) override;
		virtual void SetChannelGroupVolume(unsigned int groupID, float volume) override;
		virtual void SetChannelGroupPitch(unsigned int groupID, float volume) override;
		virtual void SetChannelGroupPan(unsigned int groupID, float volume) override;

		virtual void AddReverbToChannel(unsigned int channelID, float decay, float density, float diffusion) override;
		virtual void AddLowPassToChannel(unsigned int channelID, unsigned int limit) override;
		virtual void AddHighPassToChannel(unsigned int channelID, unsigned int limit) override;
		virtual void AddDistortionToChannel(unsigned int channelID, float level) override;
		virtual void AddChorusToChannel(unsigned int channelID, unsigned int mix, float rate, unsigned int depth) override;

		virtual void AddReverbToChannelGroup(unsigned int channelGroupID, float decay, float density, float diffusion) override;
		virtual void AddLowPassToChannelGroup(unsigned int channelGroupID, unsigned int limit) override;
		virtual void AddHighPassToChannelGroup(unsigned int channelGroupID, unsigned int limit) override;
		virtual void AddDistortionToChannelGroup(unsigned int channelGroupID, float level) override;
		virtual void AddChorusToChannelGroup(unsigned int channelGroupID, unsigned int mix, float rate, unsigned int depth) override;

		virtual void SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up) override;
		virtual void AddPolygon(float direct, float reverb, bool doublesided, const std::vector<glm::vec3>& vertices, const glm::vec3& position) override;
	};
}
