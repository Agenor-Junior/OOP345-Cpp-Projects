//Name: Agenor Junior
//ID:138121223

#include "book.h"
#include "settings.h"
#include <sstream>
#include<iomanip>
namespace seneca {
    Book::Book() : MediaItem("", "", 0), m_author(""), m_country(""), m_price(0) {}
    void Book::display(std::ostream& out) const
    {
        {
            if (g_settings.m_tableView)
            {
                out << "B | ";
                out << std::left << std::setfill('.');
                out << std::setw(50) << this->getTitle() << " | ";
                out << std::right << std::setfill(' ');
                out << std::setw(2) << this->m_country << " | ";
                out << std::setw(4) << this->getYear() << " | ";
                out << std::left;
                if (g_settings.m_maxSummaryWidth > -1)
                {
                    if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                        out << this->getSummary();
                    else
                        out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
                }
                else
                    out << this->getSummary();
                out << std::endl;
            }
            else
            {
                size_t pos = 0;
                out << this->getTitle() << " [" << this->getYear() << "] [";
                out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
                out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
                while (pos < this->getSummary().size())
                {
                    out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                    pos += g_settings.m_maxSummaryWidth;
                }
                out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                    << std::setfill(' ') << '\n';
            }
        }

    }

    Book* Book::createItem(const std::string& strBook)
    {
       
        if (strBook.empty() || strBook[0] == '#') {
            throw "Not a valid book.";
        }

        // Format: "AUTHOR,TITLE,COUNTRY,PRICE,YEAR,SUMMARY"
        std::string temp = strBook;
        size_t pos = 0;

        // AUTHOR
        pos = temp.find(',');
        std::string strAuthor = temp.substr(0, pos);
        MediaItem::trim(strAuthor);
        temp = temp.substr(pos + 1);

        // TITLE
        pos = temp.find(',');
        std::string strTitle = temp.substr(0, pos);
        MediaItem::trim(strTitle);
        temp = temp.substr(pos + 1);

        // COUNTRY
        pos = temp.find(',');
        std::string strCountry = temp.substr(0, pos);
        MediaItem::trim(strCountry);
        temp = temp.substr(pos + 1);

        // PRICE
        pos = temp.find(',');
        std::string strPrice = temp.substr(0, pos);
        double price = std::stod(strPrice);
        temp = temp.substr(pos + 1);

        // YEAR
        pos = temp.find(',');
        std::string strYear = temp.substr(0, pos);
        unsigned short year = static_cast<unsigned short>(std::stoi(strYear));
        temp = temp.substr(pos + 1);

        // SUMMARY
        MediaItem::trim(temp);
        std::string summary = temp;

        // Create and return Book instance
        return new Book(strTitle, summary, year, strAuthor, strCountry, price);
    }
}