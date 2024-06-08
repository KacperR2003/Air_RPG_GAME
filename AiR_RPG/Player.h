#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Player : public Character {
public:
    Player(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);

    void Initialize();
    void Load();
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    bool CheckCollision(const sf::RectangleShape& other);
    sf::RectangleShape& GetBoundingRectangle();
    void RevertMove();
    sf::Sprite getSprite() const;
    std::vector<std::string> getInventory() const;
    void useItem(const std::string& item);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    sf::Vector2f lastValidPosition;
    std::vector<std::string> inventory;

    void removeItem(const std::string& item);
};