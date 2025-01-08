#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <chrono>
#include <string>
#include "event.h"

namespace seneca
{
    class TimeMonitor
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
        const char *m_currentEventName;
        bool m_eventInProgress;

    public:
        TimeMonitor();
        void startEvent(const char *name);
        Event stopEvent();
    };
}

#endif