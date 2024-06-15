#pragma once
#include <string>

class Character {
public:
    Character(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);

    virtual ~Character() = default; // Wirtualny destruktor dla poprawnego usuwania obiektów klas pochodnych

    const std::string& getName() const;
    int getHealth() const;

    virtual void basicAttack(Character& opponent); // Funcka virtualna do dziedzczenia w klasie Player i Enemy
    virtual void specialAttack(Character& opponent); 

    std::string name;
    int health;
    int basicAttackDamage;
    int specialAttackDamage;
};
