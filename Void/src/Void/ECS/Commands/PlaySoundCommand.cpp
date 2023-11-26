#include "pch.h"
#include "PlaySoundCommand.h"

namespace Void{
	void PlaySoundCommand::Execute()
	{
		m_AudioManager.PlayAudio(m_AudioPath, m_ChannelGroup);
	}
}