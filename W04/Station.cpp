#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca {


	
	size_t Station::m_widthField = 0;

	
	size_t Station::id_generator = 0;

	Station::Station(const std::string& str) {
		//use utilities obj
		Utilities util;

		size_t next_pos = 0;
		
		bool more = true;

				//extract name
		m_name = util.extractToken(str, next_pos, more);
		
		////extract  serial number
		m_serialNumber = std::stoul(util.extractToken(str, next_pos, more));
	
		//extract  quantity in stock
		m_qtyInStock = std::stoul(util.extractToken(str, next_pos, more));

		//update m_widthField to max m_widthField
		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}

		//extract  description
		m_desc = util.extractToken(str, next_pos, more);

		//increment id
		m_id = ++id_generator;
	}

	size_t Station::getId() const {
		//return id
		return m_id;
	}

	const std::string& Station::getItemName() const {

		//return name of current station
		return m_name;
	}

	size_t Station::getNextSerialNumber() {
		//return next serial number increment current serial number
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const {
		//return remaining quantity
		return m_qtyInStock;
	}

	void Station::updateQuantity() {
		//update quantity 
		//subtract 1 quantity quantity max=0
		if (m_qtyInStock > 0) {
			--m_qtyInStock;
		}
	}
	//display function
	void Station::display(std::ostream& os, bool full) const {
		// `ID | NAME | SERIAL | `
		os << std::setw(3) << std::right << std::setfill('0') << m_id << " | "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | "
			<< std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";
		if (full) {
			os << std::setw(4) << std::setfill(' ') << m_qtyInStock << " | "
				<< m_desc;
		}
		os << std::endl;
	}
} // namespace seneca