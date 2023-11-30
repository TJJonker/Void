#pragma once
#include "Void/Audio/AudioManager/AudioManager.h"
#include "Void/Platform/FMOD/AudioLibrary/FMODAudioLibrary.h"
#include "Void/Platform/FMOD/DataStructs/FMODChannel.h"
#include "Void/Platform/FMOD/DataStructs/FMODChannelGroup.h"
#include <Void/Utils/ObjectPooling/Pool.h>

namespace Void::Audio {
	class FMODAudioManager : public AudioManager
	{
	public:
		FMODAudioManager();

		virtual void Initialize(unsigned int maxChannels) override;
		virtual void Update() override;
		virtual void Destroy() override;

		virtual void LoadAudio(const char* filePath) override;
		virtual void LoadStream(const char* filePath) override;
		virtual void Load3DAudio(const char* filePath, bool loop = false) override;

		virtual unsigned int PlayAudio(const char* filePath, int channelGroupIndex) override;
		virtual void StopAudio(unsigned int channelIndex) override;

		virtual void SetChannelVolume(unsigned int channelIndex, unsigned int volume) override;
		virtual void SetChannelPitch(unsigned int channelIndex, float pitch) override;
		virtual void SetChannelPan(unsigned int channelIndex, float pan) override;

		virtual void SetChannelGroupVolume(unsigned int channelGroupIndex, unsigned int volume) override;
		virtual void SetChannelGroupPitch(unsigned int channelGroupIndex, float pitch) override;
		virtual void SetChannelGroupPan(unsigned int channelGroupIndex, float pan) override;

		virtual void AddReverbToChannel(unsigned int channelIndex, float decay, float density, float diffusion) override;
		virtual void AddLowPassToChannel(unsigned int channelIndex, unsigned int cutoff) override;
		virtual void AddHighPassToChannel(unsigned int channelIndex, unsigned int cutoff) override;
		virtual void AddDistortionToChannel(unsigned int channelIndex, float level) override;
		virtual void AddChorusToChannel(unsigned int channelIndex, unsigned int mix, float rate, unsigned int depth) override;

		virtual void AddReverbToChannelGroup(unsigned int channelGroupIndex, float decay, float density, float diffusion) override;
		virtual void AddLowPassToChannelGroup(unsigned int channelGroupIndex, unsigned int cutoff) override;
		virtual void AddHighPassToChannelGroup(unsigned int channelGroupIndex, unsigned int cutoff) override;
		virtual void AddDistortionToChannelGroup(unsigned int channelGroupIndex, float level) override;
		virtual void AddChorusToChannelGroup(unsigned int channelGroupIndex, unsigned int mix, float rate, unsigned int depth) override;

		virtual void SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up) override;
		virtual unsigned int AddPolygon(float direct, float reverb, bool doublesided, const std::vector<glm::vec3>& vertices, const glm::vec3& position) override;

		virtual bool IsValid(unsigned int channelID);
		virtual void SetChannelAttributes(unsigned int channelID, const glm::vec3& position, const glm::vec3 velocity);
	
	private:
		FMOD::DSP* CreateReverbDSP(float decay, float density, float diffusion);
		FMOD::DSP* CreateLowPassDSP(unsigned int cutoff);
		FMOD::DSP* CreateHighPassDSP(unsigned int cutoff);
		FMOD::DSP* CreateDistortionDSP(float level);
		FMOD::DSP* CreateChorusDSP(unsigned int mix, float rate, unsigned int depth);

	private:
		FMOD::System* m_System = nullptr;
		FMODAudioLibrary* m_Library = nullptr;

		std::vector<ChannelGroup*> m_ChannelGroups;
		Pool<Channel>* m_ChannelsPool;
		FMOD::Geometry* m_Geometry;
	};
}
