#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>

namespace seneca
{
    enum class PartOfSpeech
    {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    struct Word
    {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary
    {
        Word *m_wordsArray;
        int m_size;

    public:
        Dictionary();
        Dictionary(const char *filename);
        ~Dictionary();
        Dictionary& operator=(const Dictionary& other);
        Dictionary(const Dictionary& other);
        //move operators
        Dictionary(Dictionary&& other) noexcept;
        Dictionary& operator=(Dictionary&& other) noexcept;
        void searchWord(const char *word);
        PartOfSpeech parsePartOfSpeech(const std::string& posStr);
        std::string getPartOfSpeechString(PartOfSpeech pos);
    };
}

#endif