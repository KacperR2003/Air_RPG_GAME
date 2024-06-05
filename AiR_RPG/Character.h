#pragma once
#include <string>

class Character {
public:
    Character(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);

    const std::string& getName() const;
    int getHealth() const;

    void basicAttack(Character& opponent);
    void specialAttack(Character& opponent);

protected:
    std::string name;
    int health;
    int basicAttackDamage;
    int specialAttackDamage;
};
