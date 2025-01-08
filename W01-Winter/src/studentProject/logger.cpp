#include <iostream>
#include "event.h"
#include "logger.h"

namespace seneca
{

    Logger::Logger() : m_eventsArray(nullptr), m_size(0), m_capacity(0) {};
    Logger::~Logger() { delete[] m_eventsArray; };
    Logger::Logger(Logger &&src)
        : m_eventsArray(src.m_eventsArray), m_size(src.m_size), m_capacity(src.m_capacity)
    {
        src.m_eventsArray = nullptr;
        src.m_size = 0;
        src.m_capacity = 0;
    };

    Logger &Logger::operator=(Logger &&src)
    {
        if (this != &src)
        {
            delete[] m_eventsArray;

            m_eventsArray = src.m_eventsArray;
            m_size = src.m_size;
            m_capacity = src.m_capacity;

            src.m_eventsArray = nullptr;
            src.m_size = 0;
            src.m_capacity = 0;
        }
        return *this;
    };

    void Logger::addEvent(const Event &event)
    {

        if (m_size == m_capacity)
        {
            int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            resizeArray(newCapacity);
        }
        m_eventsArray[m_size] = event;
        m_size++;
    };

    void Logger::resizeArray(int newCapacity)
    {
        Event *newArray = new Event[newCapacity];

        for (int i = 0; i < m_size; ++i)
        {
            newArray[i] = m_eventsArray[i];
        }

        delete[] m_eventsArray;

        m_eventsArray = newArray;
        m_capacity = newCapacity;
    }
    std::ostream &operator<<(std::ostream &os, const Logger &e)
    {
        for (int i = 0; i < e.m_size; ++i)
        {
            os << e.m_eventsArray[i] << std::endl;
        }
        return os;
    }
}