#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage)
    : Character(name, health, basicAttackDamage, specialAttackDamage) {}

sf::Sprite Enemy::getSprite() const {
    return sprite;
}

void Enemy::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);
    boundingRectangle.setSize(sf::Vector2f(64, 64));
}

void Enemy::Load() {
    if (texture.loadFromFile("Assets/Enemy/Textures/ruch.png")) {
        std::cout << "Enemy Images G!" << std::endl;
        sprite.setTexture(texture);
        sprite.setPosition(300, 800);
        int XIndex = 8;
        int YIndex = 3;
        sprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        sprite.scale(sf::Vector2f(1, 1));
    }
    else {
        std::cout << "Enemy imagine kaput!" << std::endl;
    }
}

void Enemy::Update(sf::RenderWindow& window) {
    sf::Vector2f position = sprite.getPosition();
    boundingRectangle.setPosition(sprite.getPosition());
    int squareSize = 100;
    int startX = 300;
    int startY = 800;
    float speed = 0.1;

    if (position.x < startX + squareSize && position.y == startY) {
        position.x += speed;
    }
    else if (position.x >= startX + squareSize && position.y < startY + squareSize) {
        position.y += speed;
    }
    else if (position.y >= startY + squareSize && position.x > startX) {
        position.x -= speed;
    }
    else if (position.x <= startX && position.y > startY) {
        position.y -= speed;
    }

    sprite.setPosition(position);
}

void Enemy::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(boundingRectangle);
}

sf::RectangleShape Enemy::getBoundingRectangle() const {
    return boundingRectangle;
}

void Enemy::performRandomAttack(Character& opponent) {
    int attackType = std::rand() % 2;
    if (attackType == 0) {
        basicAttack(opponent);
    }
    else {
        specialAttack(opponent);
    }
}

void Enemy::drop() {
    // Implement drop logic here
}
