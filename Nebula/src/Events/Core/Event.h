#pragma once
#include "Events/Core/IEventCommand.h"
#include <vector>

namespace Nebula::Events {
    template <typename T>
    class Event {
    public:
        // Add and remove listeners
        void AddCommand(IEventCommand<T>* listener) {
            m_Commands.push_back(listener);
        }

        void RemoveCommand(IEventCommand<T>* listener) {
            m_Commands.erase(std::remove(m_Commands.begin(), m_Commands.end(), command), m_Commands.end());
        }

        // Notify listeners with the event data
        void Trigger(T& data) {
            for (IEventCommand<T>* command : m_Commands)
                command->Execute(data);
        }

    private:
        std::vector<IEventCommand<T>*> m_Commands;
    };
}