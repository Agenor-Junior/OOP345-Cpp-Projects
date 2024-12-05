#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

namespace seneca {	

	//struture Item
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	//class customerOrder
	class CustomerOrder {

		//name of customer 
		std::string m_name{ "" };

		//name of product 
		std::string m_product{ "" };

		//count number of items in customer order
		size_t m_cntItem{ 0 };

		//dynamically allocated pointer set to null
		Item** m_lstItem{ nullptr };

		//store maximum width of field
		static size_t m_widthField;

	public:

		//default constructor
		CustomerOrder() = default;

		//constructor with 1 argument
	    CustomerOrder(const std::string& str);

		//copy constructor
		CustomerOrder(const CustomerOrder& src);
		//copy constructor prevent copy
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		
		//move constructor
		CustomerOrder(CustomerOrder&& src) noexcept;
		
		//move constructor operator
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		
		//destructor
		~CustomerOrder();

		//check if order is filled
		bool isOrderFilled() const;

		//check if item is filled
		bool isItemFilled(const std::string& itemName) const;

		//fill one item to current obj
		void fillItem(Station& station, std::ostream& os);
		//display
		void display(std::ostream& os) const;
	};

} //namespace seneca	

#endif // !SENECA_CUSTOMERORDER_H
