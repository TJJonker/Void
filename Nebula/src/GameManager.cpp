#include "GameManager.h"
// I was messing around with the oneliners, see how it looks. That's why there is a inconsistency.

class GameManager::Impl {
private:
	Void::Entity m_Player;
	std::vector<Void::Entity> m_Enemies;
	std::vector<Void::Entity> m_Humans;

	glm::vec2 m_LevelSize;

public:
	void Intialize(glm::vec2 levelSize) {
		m_LevelSize = levelSize;
	}

	void StartRound() {
		// Spawn X amount of enemies

		// Spawn player in the middle

		// Spawn Humans

	}

	void EndRound() {
		// Remove all enemies

		// Remove player

		// Remove Humans

	}
};

GameManager::GameManager() : impl(std::make_unique<Impl>()) {}

GameManager::~GameManager() = default;

void GameManager::Initiaize(glm::vec2 levelSize) { impl->Intialize(levelSize); }

void GameManager::StartRound() { impl->StartRound(); }

void GameManager::EndRound() { impl->EndRound(); }

// TODO: Implement
GameManager::DataContainer GameManager::GetData(DataType dataType) {  }

GameManager& GameManager::GetInstance() {
	static GameManager instance;
	return instance;
}