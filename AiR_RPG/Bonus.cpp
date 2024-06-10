#include "Bonus.h"

Bonus::Bonus(const std::string& name, int additionalDamage, int duration)
    : name(name), additionalDamage(additionalDamage), remainingTurns(duration) {}

std::string Bonus::getName() const {
    return name;
}

int Bonus::getAdditionalDamage() const {
    return additionalDamage;
}

int Bonus::getRemainingTurns() const {
    return remainingTurns;
}

void Bonus::decrementTurn() {
    if (remainingTurns > 0) {
        remainingTurns--;
    }
}