#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {

	class Utilities
	{
		//length of the token set default to 1
		size_t m_widthField = 1;

		//deliminator to seperate tokens 
		static char m_delimiter;
	public:

		//set current obj to value of parameter newWidth
		void setFieldWidth(size_t newWidth);

		//return field width
		size_t getFieldWidth() const;

		//function to extract tokens
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		
		
		//set deliminator to character received
		static void setDelimiter(char newDelimiter);

		//retuen deliminator
		const static char getDelimiter();
	};

} // namespace seneca
#endif // !SENECA_UTILITIES_H