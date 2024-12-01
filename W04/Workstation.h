#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <iostream>
#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
	extern std::deque<seneca::CustomerOrder> g_pending;
	extern std::deque<seneca::CustomerOrder> g_completed;
	extern std::deque<seneca::CustomerOrder> g_incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation = nullptr;

	public:

		Workstation(const std::string& str) : Station(str) {}
		Workstation& operator=(Workstation&&) = delete;
		Workstation& operator+=(CustomerOrder&& newOrder);
		Workstation(Workstation&&) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
	};

} // namespace seneca

#endif // !SENECA_WORKSTATION_H