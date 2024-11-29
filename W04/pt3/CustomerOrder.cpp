#include <iostream>
#include <string>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"


namespace seneca {

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);
        m_cntItem = 0;
        size_t temp_pos = next_pos;
        while (more) {
            util.extractToken(record, temp_pos, more);
            m_cntItem++;
        }
        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0; i < m_cntItem; ++i) {
            m_lstItem[i] = new Item(util.extractToken(record, next_pos, more));
        }
        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder&) {
        throw std::runtime_error("Copying CustomerOrder is not allowed.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product
                        << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product
                        << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber
                << "] " << std::setw(m_widthField) << std::setfill(' ') << std::left
                << m_lstItem[i]->m_itemName << " - "
                << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }

} // namespace seneca


