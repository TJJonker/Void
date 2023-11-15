#pragma once
#include <Void.h>
#include <Void.h>

class GameManager
{
public:
	enum class DataType {
		TRANSFORM_HUMAN, TRANSFORM_PLAYER,
		LOCATION_RANDOM
	};

	struct DataContainer {
		Void::TransformComponent* TransformComponent;
		glm::vec2 Position;
	};

	GameManager();
	~GameManager();

	void Initiaize(glm::vec2 levelSize);

	void StartRound();
	void EndRound();

	DataContainer GetData(DataType dataType);

	static GameManager& GetInstance();

private:
	class Impl;
	std::unique_ptr<Impl> impl;
};

