#pragma once
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "mediaItem.h"
#include<iostream>
#include<iomanip>
#include<string>
namespace seneca{

	class Book : public MediaItem {

		std::string m_author;
		std::string m_country;
		double m_price;
		Book();
		/*Book(const std::string& author, const std::string& title, const std::string& country, double price, unsigned short
			year, const std::string& summary)
			: MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {}*/
		Book(const std::string& title, const std::string& summary, unsigned short year,
			const std::string& author, const std::string& country, double price)
			: MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {}

	public:
		void display(std::ostream& out) const override;
		static Book* createItem(const std::string& strBook);
	};
}

#endif 