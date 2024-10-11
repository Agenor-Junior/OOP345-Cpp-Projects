#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <vector>
#include <iostream>
#include <algorithm>

namespace seneca {

    class Team {
        std::vector<Character*> members;
        std::string name;

    public:
        Team(const char* name = "No team") : name(name) {}

        // Rule of 5: Copy constructor
        Team(const Team& other) : name(other.name) {
            for (auto member : other.members) {
                members.push_back(member->clone());
            }
        }

        // Rule of 5: Copy assignment operator
        Team& operator=(const Team& other) {
            if (this != &other) {
                // Clean up existing members
                for (auto member : members) {
                    delete member;
                }
                members.clear();

                // Copy new members
                name = other.name;
                for (auto member : other.members) {
                    members.push_back(member->clone());
                }
            }
            return *this;
        }

        // Rule of 5: Move constructor
        Team(Team&& other) noexcept
            : members(std::move(other.members)), name(std::move(other.name)) {
            other.members.clear();
        }

        // Rule of 5: Move assignment operator
        Team& operator=(Team&& other) noexcept {
            if (this != &other) {
                // Clean up existing members
                for (auto member : members) {
                    delete member;
                }
                members = std::move(other.members);
                name = std::move(other.name);
                other.members.clear();
            }
            return *this;
        }

        // Rule of 5: Destructor
        ~Team() {
            for (auto member : members) {
                delete member;
            }
        }

        void addMember(const Character* c) {
            // Check if a character with the same name already exists
            for (auto member : members) {
                if (member->getName() == c->getName()) return;
            }
            members.push_back(c->clone());
        }

        void removeMember(const std::string& c) {
            auto it = std::remove_if(members.begin(), members.end(),
                [&](Character* member) {
                    if (member->getName() == c) {
                        delete member;
                        return true;
                    }
                    return false;
                });
            members.erase(it, members.end());
        }

        Character* operator[](size_t idx) const {
            return (idx < members.size()) ? members[idx] : nullptr;
        }

        void showMembers() const {
            std::cout << "[Team] " << name << std::endl;
            for (size_t i = 0; i < members.size(); ++i) {
                std::cout << "    " << (i + 1) << ": " << members[i]->getName() << std::endl;
            }
            if (members.empty()) std::cout << "No team." << std::endl;
        }
    };

} // namespace seneca

#endif
