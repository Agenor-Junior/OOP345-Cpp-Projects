#ifndef CHARACTER_TPL_H
#define CHARACTER_TPL_H

#include "character.h"
#include <iostream>

namespace seneca {

    template <typename T>
    class CharacterTpl : public Character {
        T m_health;
        int m_healthMax;

    public:
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax(healthMax) {
            setHealth(healthMax); // Inicializa a saúde após a construção
        }

        void takeDamage(int dmg) override {
            m_health -= dmg;
            if (static_cast<int>(m_health) <= 0) {
                m_health = 0;
                std::cout << getName() << " has been defeated!" << std::endl;
            }
            else {
                std::cout << getName() << " took " << dmg << " damage, "
                    << static_cast<int>(m_health) << " health remaining." << std::endl;
            }
        }

        int getHealth() const override {
            return static_cast<int>(m_health);
        }

        int getHealthMax() const override {
            return m_healthMax;
        }

        void setHealth(int health) override {
            m_health = health;
        }

        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }
    };

} // namespace seneca

#endif



