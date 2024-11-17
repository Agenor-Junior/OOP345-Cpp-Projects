//Name: Agenor Junior
//ID:138121223

#include "tvShow.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "settings.h"
namespace seneca {
    TvShow::TvShow() : MediaItem("", "", 0), m_id("") {}

    TvShow::TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary) :
        MediaItem(title, summary, year), m_id(id) {}


    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.') << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ') << std::setw(2) << m_episodes.size() << " | ";
            out << std::setw(4) << getYear() << " | ";
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << getSummary();
                else
                    out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << getSummary();
            out << std::endl;
        }
        else
        {
            out << getTitle() << " [" << getYear() << "]\n";
            out << std::string(getTitle().size() + 7, '-') << '\n';
            size_t pos = 0;
            while (pos < getSummary().size())
            {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (const auto& episode : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    S" << std::setw(2) << episode.m_season
                    << "E" << std::setw(2) << episode.m_numberInSeason << " ";
                if (!episode.m_title.empty())
                    out << episode.m_title << '\n';
                else
                    out << "Episode " << episode.m_numberOverall << '\n';

                pos = 0;
                while (pos < episode.m_summary.size())
                {
                    out << "            " << episode.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::string(getTitle().size() + 7, '-') << std::setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const std::string& strTvShow)
    {
      
      
        
            if (strTvShow.empty() || strTvShow[0] == '#') {
                throw "Not a valid show.";
            }

            // Format: "ID,TITLE,YEAR,SUMMARY"
            std::string temp = strTvShow;
            size_t pos = 0;

            // ID
            pos = temp.find(',');
            std::string id = temp.substr(0, pos);
            MediaItem::trim(id);
            temp = temp.substr(pos + 1);

            // TITLE
            pos = temp.find(',');
            std::string title = temp.substr(0, pos);
            MediaItem::trim(title);
            temp = temp.substr(pos + 1);

            // YEAR
            pos = temp.find(',');
            std::string strYear = temp.substr(0, pos);
            MediaItem::trim(strYear);
            unsigned short year = static_cast<unsigned short>(std::stoi(strYear));
            temp = temp.substr(pos + 1);

            // SUMMARY
            MediaItem::trim(temp);
            std::string summary = temp;

            // Use the parameterized constructor of TvShow
            return new TvShow(id, title, year, summary);
        
    }
   


    double TvShow::getEpisodeAverageLength() const
    {

        return std::accumulate(m_episodes.begin(), m_episodes.end(), (double)0,
            [&](double total, const TvEpisode& ep)
            {
                return total + ep.m_length;
            }) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const
    {
        std::list<std::string> longEpisode;

        std::for_each(m_episodes.begin(), m_episodes.end(), [&](const TvEpisode& episode)
            {
                if (episode.m_length >= 3600)
                {
                    longEpisode.push_back(episode.m_title);
                }
            });
        return longEpisode;
    }
    unsigned int TvShow::calculateSeconds(std::string& strTime)
    {
        // Format: "HH:MM:SS"
        if (strTime.find(':') != std::string::npos) {
            strTime.replace(strTime.find(':'), 1, " ");
        }
        if (strTime.find(':') != std::string::npos) {
            strTime.replace(strTime.find(':'), 1, " ");
        }
        if (strTime.find('.') != std::string::npos) {
            strTime.replace(strTime.find('.'), 1, " ");
        }
        std::stringstream ss(strTime);
        unsigned int hours = 0, minutes = 0, seconds = 0;
        ss >> hours >> minutes >> seconds;
        return hours * 3600 + minutes * 60 + seconds;

        return 0;
    }
}
