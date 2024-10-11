#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <vector>
#include <iostream>
#include <algorithm>

namespace seneca {

    class Guild {
        std::vector<Character*> members;
        std::string name;

    public:
        Guild(const char* name = "No guild") : name(name) {}

        // Rule of 5: Copy constructor
        Guild(const Guild& other) : name(other.name) {
            for (auto member : other.members) {
                Character* clonedMember = member->clone();
                clonedMember->setHealthMax(clonedMember->getHealthMax() + 300);
                members.push_back(clonedMember);
            }
        }

        // Rule of 5: Copy assignment operator
        Guild& operator=(const Guild& other) {
            if (this != &other) {
                // Clean up existing members
                for (auto member : members) {
                    delete member;
                }
                members.clear();

                // Copy new members
                name = other.name;
                for (auto member : other.members) {
                    Character* clonedMember = member->clone();
                    clonedMember->setHealthMax(clonedMember->getHealthMax() + 300);
                    members.push_back(clonedMember);
                }
            }
            return *this;
        }

        // Rule of 5: Move constructor
        Guild(Guild&& other) noexcept
            : members(std::move(other.members)), name(std::move(other.name)) {
            other.members.clear();
        }

        // Rule of 5: Move assignment operator
        Guild& operator=(Guild&& other) noexcept {
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
        ~Guild() {
            for (auto member : members) {
                delete member;
            }
        }

        void addMember(Character* c) {
            // Check if the character is already in the guild
            for (auto member : members) {
                if (member->getName() == c->getName()) return;
            }
            Character* clonedMember = c->clone();
            clonedMember->setHealthMax(clonedMember->getHealthMax() + 300);
            members.push_back(clonedMember);
        }

        void removeMember(const std::string& c) {
            auto it = std::remove_if(members.begin(), members.end(),
                [&](Character* member) {
                    if (member->getName() == c) {
                        member->setHealthMax(member->getHealthMax() - 300);
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
            std::cout << "[Guild] " << name << std::endl;
            for (size_t i = 0; i < members.size(); ++i) {
                std::cout << "    " << (i + 1) << ": " << members[i]->getName() << std::endl;
            }
            if (members.empty()) std::cout << "No guild." << std::endl;
        }
    };

} // namespace seneca

#endif
