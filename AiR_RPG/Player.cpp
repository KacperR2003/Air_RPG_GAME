#include "Player.h"
#include <iostream>

void Player::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);

    boundingRectangle.setSize(sf::Vector2f(64, 64));
}

void Player::Load()
{
    //-------------------------------- Player --------------------------------
    if (texture.loadFromFile("Assets/Player/Textures/ruch.png"))
    {
        std::cout << "Hero Images G!" << std::endl;
        sprite.setTexture(texture);

        int XIndex = 0;
        int YIndex = 2;

        sprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        sprite.scale(sf::Vector2f(1, 1));
        sprite.setPosition(sf::Vector2f(980, 560));
    }
    else
    {
        std::cout << "Hero imagine kaput!" << std::endl;
    }
}

void Player::Update(sf::RenderWindow& window)
{
    //-------------------------------- RUCH --------------------------------
    sf::Vector2f position = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        position.x += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        position.x -= 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        position.y += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        position.y -= 1;

    // Pobranie rozmiaru okna
    sf::Vector2u windowSize = window.getSize();

    // Dodanie ograniczeñ, aby gracz nie móg³ wyjœæ poza granice okna
    if (position.x < 0)
        position.x = 0;
    if (position.y < 0)
        position.y = 0;
    if (position.x + boundingRectangle.getSize().x > windowSize.x)
        position.x = windowSize.x - boundingRectangle.getSize().x;
    if (position.y + boundingRectangle.getSize().y > windowSize.y)
        position.y = windowSize.y - boundingRectangle.getSize().y;

    sprite.setPosition(position);
    boundingRectangle.setPosition(position);
    //-------------------------------- RUCH --------------------------------

    // Zapisanie ostatniej poprawnej pozycji gracza
    lastValidPosition = position;
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(boundingRectangle);
}

bool Player::CheckCollision(const sf::RectangleShape& other)
{
    return boundingRectangle.getGlobalBounds().intersects(other.getGlobalBounds());
}

Player::Player(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage)
    : Character(name, health, basicAttackDamage, specialAttackDamage) {}

sf::RectangleShape& Player::GetBoundingRectangle()
{
    return boundingRectangle;
}

void Player::RevertMove()
{
    // Przywróæ ostatni¹ poprawn¹ pozycjê gracza
    sprite.setPosition(lastValidPosition);
    boundingRectangle.setPosition(lastValidPosition);
}
