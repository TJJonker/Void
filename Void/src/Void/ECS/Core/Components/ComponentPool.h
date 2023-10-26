#pragma once
struct ComponentPool
{
	const int MAX_ENTITIES = 32;

	char* data = nullptr;
	size_t elementSize = 0;

	ComponentPool(size_t elementSize);
	~ComponentPool();
	void* Get(size_t index);
};

