#include "Utilities.h"
#include "Station.h"


namespace seneca {
    //set value for deliminator
    char Utilities::m_delimiter = '\n';
    //set current obj to value of parameter newWidth
    void Utilities::setFieldWidth(size_t newWidth) {
        //set witdth as parameter
        m_widthField = newWidth;
    }

    //return field width
    size_t Utilities::getFieldWidth() const {
        //return field of current obj
        return m_widthField;
    }

    //extrtact tokens
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {       
        //extract token from str starting at next_pos
        if (next_pos >= str.length()) {
            
            //set more to true
            more = false;
            //return ""
            return "";
        }
        //reports exception if delimaintor found at next position
        size_t pos = str.find(m_delimiter, next_pos);
        std::string token;

        //if pos !=npos
        if (pos != std::string::npos) {
            //set token
            token = str.substr(next_pos, pos - next_pos);
            //+ to next_pos
            next_pos = pos + 1;

            //set more to true
            more = true;
        }
        else {
            //set token to 
            token = str.substr(next_pos);
            //set next pos to arg.length
            next_pos = str.length();
            //set more to false
            more = false;
        }
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        //id token empty
        if (token.empty()) {
            //set more to false
            more = false;
            //throw exception
            throw "No token found!";
        }

        //if m_widthField<token,length
        if (m_widthField < token.length()) {
            //set m_width to token.lemgth
            m_widthField = token.length();
        }

        //return token
        return token;
    }

    //set deliminator
    void Utilities::setDelimiter(char newDelimiter) {
        //set deliminator for this class to chnaracter received
        m_delimiter = newDelimiter;
    }

    //return deliminator for this class
    const char Utilities::getDelimiter() {
        //return deiminator
        return m_delimiter;
    }

} // namespace seneca