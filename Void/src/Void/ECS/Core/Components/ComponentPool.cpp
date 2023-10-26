#include "pch.h"
#include "ComponentPool.h"

ComponentPool::ComponentPool(size_t elementSize)
{
    elementSize = elementSize;
    data = new char[elementSize * MAX_ENTITIES];
}

ComponentPool::~ComponentPool()
{
    delete[] data;
}

void* ComponentPool::Get(size_t index)
{
    return data + index * elementSize;
}


