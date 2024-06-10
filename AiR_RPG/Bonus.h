#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Bonus {
public:
    // Konstruktor, który inicjuje nazwê bonusu, dodatkowy damage i czas trwania
    Bonus(const std::string& name, int additionalDamage, int duration);

    // Metody dostêpu do prywatnych atrybutów
    std::string getName() const;
    int getAdditionalDamage() const;
    int getRemainingTurns() const;

    // Zmniejszenie liczby pozosta³ych tur
    void decrementTurn();

private:
    std::string name;
    int additionalDamage;
    int remainingTurns;
};
