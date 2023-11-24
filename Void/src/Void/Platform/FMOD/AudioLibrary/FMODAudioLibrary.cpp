#include "pch.h"
#include "FMODAudioLibrary.h"

namespace Void::Audio {
	FMODAudioLibrary::FMODAudioLibrary(FMOD::System* system)
		:m_System(system) { }

	void FMODAudioLibrary::Load3DAudio(const char* filePath)
	{
		VOID_ASSERT(!m_Library.count(filePath), "Entry '{0}' already exists in the library", filePath);
		
		FMOD::Sound* sound;
		FMOD_RESULT result = m_System->createSound(filePath, FMOD_3D, nullptr, &sound);
		VOID_ASSERT(result, "Failed to load the audio file: '{0}'", filePath);

		m_Library.insert({ filePath, sound });
	}

	void FMODAudioLibrary::LoadAudio(const char* filePath)
	{
		VOID_ASSERT(!m_Library.count(filePath), "Entry '{0}' already exists in the library", filePath);

		FMOD::Sound* sound;
		FMOD_RESULT result = m_System->createSound(filePath, FMOD_DEFAULT, nullptr, &sound);
		VOID_ASSERT(result, "Failed to load the audio file: '{0}'", filePath);

		m_Library.insert({ filePath, sound });
	}

	void FMODAudioLibrary::LoadStream(const char* filePath)
	{
		VOID_ASSERT(!m_Library.count(filePath), "Entry '{0}' already exists in the library", filePath);

		FMOD::Sound* sound;
		FMOD_RESULT result = m_System->createStream(filePath, FMOD_DEFAULT, nullptr, &sound);
		VOID_ASSERT(result, "Failed to load the audio file: '{0}'", filePath);

		m_Library.insert({ filePath, sound });
	}

	FMOD::Sound* FMODAudioLibrary::GetSound(const char* filePath)
	{
		VOID_ASSERT(m_Library.count(filePath), "Entry '{0}' does not exist in the audioLibrary.");
		return m_Library[filePath];
	}
}