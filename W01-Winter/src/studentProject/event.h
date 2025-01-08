#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <chrono>

namespace seneca
{
    class Event
    {
        std::string m_eventName;
        std::chrono::nanoseconds m_eventDuration;

    public:
        Event()=default;
        Event(const char *name, const std::chrono::nanoseconds &duration);
        friend std::ostream& operator<<(std::ostream& os, const Event& e);
    };
    
}

#endif