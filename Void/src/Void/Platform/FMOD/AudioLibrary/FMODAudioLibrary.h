#include <map>
#include <fmod/fmod.hpp>
#include <string>

namespace Void::Audio {
	class FMODAudioLibrary {
	private:
		FMOD::System* m_System = nullptr;
		std::map<std::string, FMOD::Sound*> m_Library = {};

	public:
		FMODAudioLibrary(FMOD::System* system);

		void Load3DAudio(const char* filePath);
		void LoadAudio(const char* filePath);
		void LoadStream(const char* filePath);

		FMOD::Sound* GetSound();
	};
}