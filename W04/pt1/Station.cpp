#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca {

	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;


	Station::Station(const std::string& str) {
		Utilities util;
		size_t next_pos = 0;
		bool more = true;

		m_name = util.extractToken(str, next_pos, more);
		m_serialNumber = std::stoul(util.extractToken(str, next_pos, more));
		m_qtyInStock = std::stoul(util.extractToken(str, next_pos, more));

		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}
		m_desc = util.extractToken(str, next_pos, more);

		m_id = ++id_generator;
	}

	size_t Station::getId() const {
		return m_id;
	}

	const std::string& Station::getItemName() const {
		return m_name;
	}

	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const {
		return m_qtyInStock;
	}

	void Station::updateQuantity() {
		if (m_qtyInStock > 0) {
			--m_qtyInStock;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << std::setw(3) << std::setfill('0') << m_id << " | "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | "
			<< std::setw(6) << std::right << m_serialNumber << " | ";

		if (full) {
			os << std::setw(4) << m_qtyInStock << " | "
				<< m_desc;
		}

		os << std::endl;
	}

} // namespace seneca
