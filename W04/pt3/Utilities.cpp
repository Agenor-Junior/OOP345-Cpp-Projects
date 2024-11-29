#include "Utilities.h"
#include "Station.h"


namespace seneca {

	char Utilities::m_delimiter = '\n';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }
        size_t pos = str.find(m_delimiter, next_pos);
        std::string token;
        if (pos != std::string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            next_pos = pos + 1;
            more = true;
        }
        else {
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        if (token.empty()) {
            more = false;
            throw "No token found!";
        }
        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	const char Utilities::getDelimiter() {
		return m_delimiter;
	}

} // namespace seneca