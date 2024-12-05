#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include "mediaItem.h"
#include "collection.h"

namespace seneca {
    class TvShow;

    struct TvEpisode {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem {
        std::string m_id{};
        std::vector<TvEpisode> m_episodes;

        TvShow();

        TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary);

    public:
        virtual ~TvShow() noexcept = default;

        void display(std::ostream& out) const override;

        static TvShow* createItem(const std::string& strTvShow);
        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;

        template <typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode);

        static unsigned int calculateSeconds(std::string& strTime);
    };

    template <typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode) {
        
        std::string temp = strEpisode;
        MediaItem::trim(temp);
        if (temp.empty() || temp[0] == '#') {
            throw "Not a valid episode.";
        }

        // Format:
        // "ID,EPISODE_NUMBER,SEASON_NUMBER,EPISODE_IN_SEASON,AIR_DATE,LENGTH,TITLE,SUMMARY"
        TvEpisode episode;
        size_t pos = 0;

        // ID
        pos = temp.find(',');
        std::string strId = temp.substr(0, pos);
        MediaItem::trim(strId);
        TvShow* show = nullptr;
        for (size_t i = 0; i < col.size(); i++) {
            show = dynamic_cast<TvShow*>(col[i]);
            if (show && show->m_id == strId) {
                episode.m_show = show;
                break;
            }
        }

        if (!show) {
            throw std::runtime_error("Invalid show ID: " + strId);
        }

        temp = temp.substr(pos + 1);

        // EPISODE_NUMBER
        pos = temp.find(',');
        std::string strEpisodeNumber = temp.substr(0, pos);
        MediaItem::trim(strEpisodeNumber);
        episode.m_numberOverall = std::stoi(strEpisodeNumber);
        temp = temp.substr(pos + 1);

        // SEASON_NUMBER
        pos = temp.find(',');
        std::string strSeason = temp.substr(0, pos);
        MediaItem::trim(strSeason);
        if (strSeason.empty()) {
            episode.m_season = 1;
        }
        else {
            episode.m_season = std::stoi(strSeason);
        }
        temp = temp.substr(pos + 1);

        // EPISODE_IN_SEASON
        pos = temp.find(',');
        std::string strEpisodeInSeason = temp.substr(0, pos);
        MediaItem::trim(strEpisodeInSeason);
        episode.m_numberInSeason = std::stoi(strEpisodeInSeason);
        temp = temp.substr(pos + 1);

        // AIR_DATE
        pos = temp.find(',');
        std::string strAirDate = temp.substr(0, pos);
        MediaItem::trim(strAirDate);
        episode.m_airDate = strAirDate;
        temp = temp.substr(pos + 1);

        // LENGTH
        pos = temp.find(',');
        std::string strLength = temp.substr(0, pos);
        MediaItem::trim(strLength);
        episode.m_length = calculateSeconds(strLength);
        temp = temp.substr(pos + 1);

        // TITLE
        pos = temp.find(',');
        std::string strTitle = temp.substr(0, pos);
        MediaItem::trim(strTitle);
        episode.m_title = strTitle;
        temp = temp.substr(pos + 1);

        // SUMMARY
        MediaItem::trim(temp);
        episode.m_summary = temp;

        show->m_episodes.push_back(episode);
    }
}

#endif //SENECA_TVSHOW_H
