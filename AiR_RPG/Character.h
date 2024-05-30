#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Character
{
public:
    std::string name;
    int health;
    int basicAttackDamage;
    int specialAttackDamage;

    Character(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);
    void basicAttack(Character& opponent);
    void specialAttack(Character& opponent);
};

