#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

class Random {
public:
    // Seed the random number generator
    static void Seed() {
        std::srand((unsigned int)std::time(nullptr));
    }

    // Generate a random float between min and max
    static float Between(float min, float max) {
        return min + static_cast<float>(std::rand()) / (RAND_MAX / (max - min));
    }
};