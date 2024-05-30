#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Enemy : public Character
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
public:
    void Load();
    void Update(sf::RenderWindow& window);
    void Initialize();
    void Draw(sf::RenderWindow& window);
    void drop();
    sf::RectangleShape getBoundingRectangle() const;
    Enemy(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);
};

