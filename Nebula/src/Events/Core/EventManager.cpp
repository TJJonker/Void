#include "EventManager.h"

namespace Nebula::Events {
    EventManager& EventManager::GetInstance()
    {
        static EventManager instance;
        return instance;
    }
}