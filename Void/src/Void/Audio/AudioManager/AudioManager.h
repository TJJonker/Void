#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace Void::Audio {
	class AudioManager
	{
	public:
		virtual void Initialize(unsigned int maxChannels) = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;

		virtual void LoadAudio(const char* filePath) = 0;
		virtual void LoadStream(const char* filePath) = 0;
		virtual void Load3DAudio(const char* filePath, bool loop = false) = 0;

		virtual unsigned int PlayAudio(const char* filePath, int channelGroupIndex) = 0;
		virtual void StopAudio(unsigned int channelID) = 0;

		virtual void SetChannelVolume(unsigned int channelID, unsigned int volume) = 0;
		virtual void SetChannelPitch(unsigned int channelID, float pitch) = 0;
		virtual void SetChannelPan(unsigned int channelID, float pan) = 0;

		virtual void SetChannelGroupVolume(unsigned int groupID, unsigned int volume) = 0;
		virtual void SetChannelGroupPitch(unsigned int groupID, float pitch) = 0;
		virtual void SetChannelGroupPan(unsigned int groupID, float pan) = 0;
		
		virtual void AddReverbToChannel(unsigned int channelID, float decay = 1500.f, float density = 100.f, float diffusion = 50.f) = 0;
		virtual void AddLowPassToChannel(unsigned int channelID, unsigned int cutoff = 5000) = 0;
		virtual void AddHighPassToChannel(unsigned int channelID, unsigned int cutoff = 5000) = 0;
		virtual void AddDistortionToChannel(unsigned int channelID, float level = .5f) = 0;
		virtual void AddChorusToChannel(unsigned int channelID, unsigned int mix = 50, float rate = .8f, unsigned int depth = 3) = 0;

		virtual void AddReverbToChannelGroup(unsigned int channelGroupID, float decay = 1500.f, float density = 100.f, float diffusion = 50.f) = 0;
		virtual void AddLowPassToChannelGroup(unsigned int channelGroupID, unsigned int cutoff = 5000) = 0;
		virtual void AddHighPassToChannelGroup(unsigned int channelGroupID, unsigned int cutoff = 5000) = 0;
		virtual void AddDistortionToChannelGroup(unsigned int channelGroupID, float level = .5f) = 0;
		virtual void AddChorusToChannelGroup(unsigned int channelGroupID, unsigned int mix = 50, float rate = .8f, unsigned int depth = 3) = 0;

		virtual void SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up) = 0;

		virtual unsigned int AddPolygon(float direct, float reverb, bool doublesided, const std::vector<glm::vec3>& vertices, const glm::vec3& position) = 0;

		virtual bool IsValid(unsigned int channelID) = 0;
		virtual void SetChannelAttributes(unsigned int channelID, const glm::vec3& position, const glm::vec3 velocity) = 0;

		static AudioManager* GetInstance();

		#define CHANNELGROUP_MASTER_INDEX	0
		#define CHANNELGROUP_MUSIC_INDEX	1
		#define CHANNELGROUP_SFX_INDEX		2

		#define DSP_REVERB_INDEX			0
		#define DSP_LOWPASS_INDEX			1
		#define DSP_HIGHPASS_INDEX			2
		#define DSP_DISTORTION_INDEX		3
		#define DSP_CHORUS_INDEX			4

		#define	DSP_AMOUNT					5

	private:
		static AudioManager* m_Instance;
	};
}
