#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Enemy : public Character {
public:
    Enemy(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);

    void Initialize();
    void Load();
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void performRandomAttack(Character& opponent);
    void drop();

    sf::RectangleShape getBoundingRectangle() const;
    sf::Sprite getSprite() const;
    std::vector<std::string> getInventory() const;
    void addItem(const std::string& item);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    std::vector<std::string> inventory;
};
