#pragma once
#include "Void/Utils/Command/ICommand.h"
#include <Void/Audio/AudioManager/AudioManager.h>

namespace Void {
	class PlaySoundCommand : public ICommand {
	public:
		PlaySoundCommand(const char* audioPath, unsigned int channelGroup, Audio::AudioManager& audioManager)
			: m_AudioPath(audioPath), m_ChannelGroup(channelGroup), m_AudioManager(audioManager) { }

		void Execute() override;

	private:
		const char* m_AudioPath;
		unsigned int m_ChannelGroup;
		Audio::AudioManager& m_AudioManager;
	};
}