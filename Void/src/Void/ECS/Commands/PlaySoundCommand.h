#pragma once
#include "Void/ECS/Event/IECSCommand.h"

namespace Void {
	class PlaySoundCommand : public IECSCommand {
	public:
		PlaySoundCommand(const char* audioPath, unsigned int channelGroup)
			: m_AudioPath(audioPath), m_ChannelGroup(channelGroup) { }

		void Execute(IECSEventInfo& info) override;

	private:
		const char* m_AudioPath;
		unsigned int m_ChannelGroup;
	};
}