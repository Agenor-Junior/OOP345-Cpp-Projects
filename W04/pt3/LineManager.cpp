#include "LineManager.h"
#include <sstream>

namespace seneca {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream inputFile(file);
        if (!inputFile) {
            throw std::runtime_error("Error: Unable to open file " + file);
        }
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream record(line);
            std::string currentStation, nextStation;
            std::getline(record, currentStation, '|');
            std::getline(record, nextStation);
            auto currentIt = std::find_if(stations.begin(), stations.end(),
                [&currentStation](Workstation* station) {
                    return station->getItemName() == currentStation;
                });
            auto nextIt = std::find_if(stations.begin(), stations.end(),
                [&nextStation](Workstation* station) {
                    return station->getItemName() == nextStation;
                });
            if (currentIt != stations.end()) {
                m_activeLine.push_back(*currentIt);
                if (nextIt != stations.end()) {
                    (*currentIt)->setNextStation(*nextIt);
                }
            }
        }
        m_firstStation = *std::find_if(stations.begin(), stations.end(),
            [&stations](Workstation* station) {
                return std::none_of(stations.begin(), stations.end(),
                [station](Workstation* other) {
                        return other->getNextStation() == station;
                    });
            });
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> reordered;
        Workstation* current = m_firstStation;
        while (current) {
            reordered.push_back(current);
            current = current->getNextStation();
        }
        m_activeLine = std::move(reordered);
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        ++iteration;
        os << "Line Manager Iteration: " << iteration << std::endl;
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&os](Workstation* station) {
                station->fill(os);
            });
        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [](Workstation* station) {
                station->attemptToMoveOrder();
            });
        return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
    }

    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&os](Workstation* station) {
                station->display(os);
            });
    }

} // namespace seneca