#include <fmod/fmod.hpp>
#include <string>
#include <unordered_map>

namespace Void::Audio {
	class FMODAudioLibrary {
	private:
		FMOD::System* m_System = nullptr;
		std::unordered_map<std::string, FMOD::Sound*> m_Library{};

	public:
		FMODAudioLibrary(FMOD::System* system);

		void Load3DAudio(const char* filePath);
		void LoadAudio(const char* filePath);
		void LoadStream(const char* filePath);

		FMOD::Sound* GetSound(const char* filePath);
	};
}