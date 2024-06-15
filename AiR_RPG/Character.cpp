#include "Character.h"
#include <iostream>

Character::Character(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage)
    : name(name), health(health), basicAttackDamage(basicAttackDamage), specialAttackDamage(specialAttackDamage) {}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

void Character::basicAttack(Character& opponent) {
    opponent.health -= basicAttackDamage;
    std::cout << name << " used Basic Attack on " << opponent.name << " for " << basicAttackDamage << " damage.\n";
}

void Character::specialAttack(Character& opponent) {
    opponent.health -= specialAttackDamage;
    std::cout << name << " used Special Attack on " << opponent.name << " for " << specialAttackDamage << " damage.\n";
}
