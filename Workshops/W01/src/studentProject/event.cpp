#include "event.h"
#include "settings.h"
#include <iomanip>
#include <cstring>
#include <chrono>


namespace seneca
{
    Event::Event(const char *name, const std::chrono::nanoseconds &duration)
        : m_eventName{name}, m_eventDuration{duration} {};
    std::ostream& operator<<(std::ostream& os, const Event& e)
    {

        static int counter = 0;
        int size = 0;
        long long durationFormat;
        if (g_settings.m_time_units == "seconds")
        {
            durationFormat = std::chrono::duration_cast<std::chrono::seconds>(e.m_eventDuration).count();
            size = 2;
        }
        else if (g_settings.m_time_units == "miliseconds")
        {
            durationFormat = std::chrono::duration_cast<std::chrono::milliseconds>(e.m_eventDuration).count();
            size = 5;
        }
        else if (g_settings.m_time_units == "microseconds")
        {
            durationFormat = std::chrono::duration_cast<std::chrono::microseconds>(e.m_eventDuration).count();
            size = 8;
        }
        else
        {
            durationFormat = std::chrono::duration_cast<std::chrono::nanoseconds>(e.m_eventDuration).count();
            size = 11;
        }

        return os << std::right << std::setw(2) << ++counter << ": "
                  << std::right << std::setw(40) << e.m_eventName << " -> "
                  << std::right << std::setw(size) << durationFormat << " " << g_settings.m_time_units;
    }
    
}