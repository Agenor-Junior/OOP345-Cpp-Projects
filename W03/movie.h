#pragma once
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <ostream>

namespace seneca {

    class Movie : public MediaItem {
    public:
        Movie();
       // Movie(const std::string& title, const std::string& summary, unsigned short year);
        Movie(const std::string& title, unsigned short year, const std::string& summary);
        void display(std::ostream& out) const override;
        static Movie* createItem(const std::string& strMovie);
    };

}
#endif
