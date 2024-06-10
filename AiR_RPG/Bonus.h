#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Bonus {
public:
    // Konstruktor, kt�ry inicjuje nazw� bonusu, dodatkowy damage i czas trwania
    Bonus(const std::string& name, int additionalDamage, int duration);

    // Metody dost�pu do prywatnych atrybut�w
    std::string getName() const;
    int getAdditionalDamage() const;
    int getRemainingTurns() const;

    // Zmniejszenie liczby pozosta�ych tur
    void decrementTurn();

private:
    std::string name;
    int additionalDamage;
    int remainingTurns;
};
