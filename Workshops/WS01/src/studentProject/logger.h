#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include "event.h"

namespace seneca
{

    class Logger
    {
        Event *m_eventsArray;
        int m_size;
        int m_capacity;

    public:
        Logger();
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        ~Logger();
        Logger(Logger &&src); 
        Logger &operator=(Logger &&src); 
        void addEvent(const Event &event);
        friend std::ostream &operator<<(std::ostream &os, const Logger &e);
        void resizeArray(int newCapacity);
    };
}

#endif