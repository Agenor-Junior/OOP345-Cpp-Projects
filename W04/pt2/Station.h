#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>

namespace seneca {

	class Station {
		size_t m_id{};
		std::string m_name{ "" };
		std::string m_desc{ "" };
		size_t m_serialNumber{};
		size_t m_qtyInStock{};
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station() = default;
		Station(const std::string& str);
		size_t getId() const;
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

} // namespace seneca

#endif // !SENECA_STATION_H
