#pragma once
#include <map>
#include <vector>
#include <string>

struct AnimationInfo {
	enum class Direction {
		LEFT, UP, RIGHT, DOWN
	};

	std::map<Direction, std::vector<std::string>> AnimationFrames;
	std::string Shader;
	std::string Texture;
};