#include "pch.h"
#include "PlaySoundCommand.h"
#include <Void/Audio/AudioManager/AudioManager.h>
#include <Void/ECS/Event/CollisionInfo.h>

namespace Void{
	void PlaySoundCommand::Execute(IECSEventInfo& info)
	{
		CollisionInfo& localInfo = static_cast<CollisionInfo&>(info);
		Audio::AudioManager::GetInstance()->PlayAudio(m_AudioPath, m_ChannelGroup);
	}
}