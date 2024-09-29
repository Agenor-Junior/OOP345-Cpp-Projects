#include "dictionary.h"
#include "settings.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

namespace seneca
{
    Dictionary::Dictionary() : m_wordsArray(nullptr), m_size(0) {}

    Dictionary::Dictionary(const char *filename)
        : m_wordsArray(nullptr), m_size(0)
    {
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return; 
        }
        
        std::vector<Word> wordsVec;
        std::string line, word, definition, posStr;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            if (std::getline(iss, word, ',') &&
                std::getline(iss, posStr, ',') &&
                std::getline(iss, definition))
            {
                Word w;
                w.m_word = word;
                w.m_pos = parsePartOfSpeech(posStr);
                w.m_definition = definition;
                wordsVec.push_back(w);
            }
        }

        m_size = wordsVec.size();
        m_wordsArray = new Word[m_size];
        for (int i = 0; i < m_size; ++i)
        {
            m_wordsArray[i] = wordsVec[i];
        }
    }

    Dictionary::~Dictionary()
    {
        delete[] m_wordsArray;
    }

    Dictionary& Dictionary::operator=(const Dictionary& other)
    {
        if (this != &other)
        {
            delete[] m_wordsArray;
            m_size = other.m_size;

            if (other.m_wordsArray)
            {
                m_wordsArray = new Word[m_size];
                for (int i = 0; i < m_size; i++)
                {
                    m_wordsArray[i].m_word = other.m_wordsArray[i].m_word;
                    m_wordsArray[i].m_definition = other.m_wordsArray[i].m_definition;
                    m_wordsArray[i].m_pos = other.m_wordsArray[i].m_pos;
                }
            }
            else
            {
                m_wordsArray = nullptr;
            }
        }
        return *this;
    }

    Dictionary::Dictionary(const Dictionary& other)
    {
        m_size = other.m_size;
        m_wordsArray = nullptr;
        if (other.m_wordsArray)
        {
            m_wordsArray = new Word[m_size];
            for (int i = 0; i < m_size; i++)
            {
                m_wordsArray[i].m_word = other.m_wordsArray[i].m_word;
                m_wordsArray[i].m_definition = other.m_wordsArray[i].m_definition;
                m_wordsArray[i].m_pos = other.m_wordsArray[i].m_pos;
            }
        }
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept
    {
        m_wordsArray = other.m_wordsArray;
        m_size = other.m_size;
        other.m_size = 0;
        other.m_wordsArray = nullptr;
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept
    {
        if (this != &other)
        {
            m_size = other.m_size;
            other.m_size = 0;
            delete[] m_wordsArray;
            m_wordsArray = other.m_wordsArray;
            other.m_wordsArray = nullptr;
        }
        return *this;
    }

    void Dictionary::searchWord(const char *word)
    {
        bool found = false;
        for (int i = 0; i < m_size; ++i)
        {
            if (m_wordsArray[i].m_word == word)
            {
                if (!found)
                {
                    std::cout << m_wordsArray[i].m_word << " - ";
                }
                else
                {
                    std::cout << std::string(strlen(word), ' ') << " - ";
                }

                if (g_settings.m_verbose && m_wordsArray[i].m_pos != PartOfSpeech::Unknown)
                {
                    std::cout << "(" << getPartOfSpeechString(m_wordsArray[i].m_pos) << ") ";
                }

                std::cout << m_wordsArray[i].m_definition << std::endl;

                found = true;

                if (!g_settings.m_show_all)
                {
                    return;
                }
            }
        }

        if (!found)
        {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

    PartOfSpeech Dictionary::parsePartOfSpeech(const std::string &posStr)
    {
        if (posStr == "n." || posStr == "n. pl.")
            return PartOfSpeech::Noun;
        if (posStr == "adv.")
            return PartOfSpeech::Adverb;
        if (posStr == "a.")
            return PartOfSpeech::Adjective;
        if (posStr == "v." || posStr == "v. i." || posStr == "v. t." || posStr == "v. t. & i.")
            return PartOfSpeech::Verb;
        if (posStr == "prep.")
            return PartOfSpeech::Preposition;
        if (posStr == "pron.")
            return PartOfSpeech::Pronoun;
        if (posStr == "conj.")
            return PartOfSpeech::Conjunction;
        if (posStr == "interj.")
            return PartOfSpeech::Interjection;

        return PartOfSpeech::Unknown;
    }

    std::string Dictionary::getPartOfSpeechString(PartOfSpeech pos)
    {
        switch (pos)
        {
        case PartOfSpeech::Noun:
            return "noun";
        case PartOfSpeech::Pronoun:
            return "pronoun";
        case PartOfSpeech::Adjective:
            return "adjective";
        case PartOfSpeech::Adverb:
            return "adverb";
        case PartOfSpeech::Verb:
            return "verb";
        case PartOfSpeech::Preposition:
            return "preposition";
        case PartOfSpeech::Conjunction:
            return "conjunction";
        case PartOfSpeech::Interjection:
            return "interjection";
        default:
            return "unknown";
        }
    }
}