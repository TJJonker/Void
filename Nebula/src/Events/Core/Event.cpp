//#pragma once
//#include "Events/Core/Event.h"
//
//namespace Nebula::Events {
//    template<typename T>
//    inline void Event<T>::AddCommand(IEventCommand<T>* command)
//    {
//        m_Listeners.push_back(listener);
//    }
//
//    template<typename T>
//    inline void Event<T>::RemoveCommand(IEventCommand<T>* command)
//    {
//        m_Commands.erase(std::remove(m_Commands.begin(), m_Commands.end(), command), m_Commands.end());
//    }
//
//    template<typename T>
//    void Event<T>::Trigger(const T& data)
//    {
//        for (IEventCommand<T>* command : m_Commands)
//            command->Execute(data);
//    }
//}