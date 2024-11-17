#include "timeMonitor.h"

namespace seneca
{
    TimeMonitor::TimeMonitor() : m_currentEventName(nullptr), m_eventInProgress(false)
    {
    }

    void TimeMonitor::startEvent(const char *name)
    {
        m_currentEventName = name;
        m_startTime = std::chrono::high_resolution_clock::now();
        m_eventInProgress = true;
    }
    Event TimeMonitor::stopEvent()
    {
        if (!m_eventInProgress)
        {
            throw std::runtime_error("No event in progress to stop.");
        }

        auto endTime = std::chrono::high_resolution_clock::now();                                             
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);


        m_eventInProgress = false;

        return Event(m_currentEventName, duration);
    }
}
