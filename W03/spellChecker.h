#pragma once
#ifndef  SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include<vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
namespace seneca {

	
	class SpellChecker {
		std::string m_badWords[6];
		std::string m_goodWords[6];
		size_t m_misCount[6];

	public:
		SpellChecker(const char* filename);

		void operator()(std::string& text);

		void showStatistics(std::ostream& out) const;
	};
}
#endif