﻿#pragma once
#include "Character.h"
#include "Map.h"
#include <SFML/Audio.hpp>
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
    sf::Vector2f getPosition() const;
    void addItem(const std::string& item);

    void basicAttack(Character& opponent) override;
    void specialAttack(Character& opponent) override;

    sf::FloatRect getBoundingBox() const {
        // Zwraca obszar zajmowany przez gracza w postaci sf::FloatRect
        return sprite.getGlobalBounds();
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    sf::Vector2f lastValidPosition;
    std::vector<std::string> inventory;
    sf::SoundBuffer moveSoundBuffer;
    sf::Sound moveSound;

    int XIndex;
    int YIndex;
    int animationFrame;
    int animationSpeed;

    void removeItem(const std::string& item);
};
