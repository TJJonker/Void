#pragma once
#include "Void/ECS/Core/Systems/ISystem.h"
#include <Void/Audio/AudioManager/AudioManager.h>

namespace Void {
	class AudioListenerSystem : public ISystem
	{
	public:
		AudioListenerSystem(Audio::AudioManager& audioManager)
			: m_AudioManager(audioManager) { }

		virtual void Update(Scene* scene) override;

	private:
		Audio::AudioManager& m_AudioManager;
	};
}