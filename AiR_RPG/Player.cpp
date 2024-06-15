#include "Player.h"
#include <iostream>

// Zakladamy, ze zmienna globalna max_health jest zadeklarowana w innym pliku (np. main.cpp)
extern int max_health;

// Constructor
Player::Player(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage)
    : Character(name, health, basicAttackDamage, specialAttackDamage) {
    inventory = { "Potion", "Elixir", "Revive" }; // Przykładowe przedmioty
    XIndex = 0;
    YIndex = 2; // Initial direction, for example
    animationFrame = 0;
    animationSpeed = 200; // Increased speed to slow down the animation
}

void Player::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);
    boundingRectangle.setSize(sf::Vector2f(64, 64));
    moveSound.setBuffer(moveSoundBuffer);
}

void Player::Load() {
    //-------------------------------- Player --------------------------------
    if (texture.loadFromFile("Assets/Player/Textures/ruch.png")) {
        std::cout << "Hero Images G!" << std::endl;
        sprite.setTexture(texture);

        sprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        sprite.scale(sf::Vector2f(1, 1));
        sprite.setPosition(sf::Vector2f(980, 560));
    }
    else {
        std::cout << "Hero imagine kaput!" << std::endl;
    }

    // Load move sound
    if (!moveSoundBuffer.loadFromFile("Assets/Player/Sounds/move.wav")) {
        std::cerr << "Dzwiek Kaput!" << std::endl;
    }

    moveSound.setBuffer(moveSoundBuffer);
}

void Player::Update(sf::RenderWindow& window) {
    //-------------------------------- RUCH --------------------------------
    sf::Vector2f position = sprite.getPosition();
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        position.x += 0.2;
        isMoving = true;
        YIndex = 3;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position.x -= 0.2;
        isMoving = true;
        YIndex = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position.y += 0.2;
        isMoving = true;
        YIndex = 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        position.y -= 0.2;
        isMoving = true;
        YIndex = 0;
    }

    // Pobranie rozmiaru okna
    sf::Vector2u windowSize = window.getSize();

    // Dodanie ograniczeń, aby gracz nie mógł wyjść poza granice okna
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

    if (isMoving) {
        // Play move sound
        if (moveSound.getStatus() != sf::Sound::Playing) {
            moveSound.play();
        }

        // Update animation
        animationFrame++;
        if (animationFrame >= animationSpeed) {
            animationFrame = 0;
            XIndex++;
            if (XIndex > 3) {
                XIndex = 0;
            }
        }
        sprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
    }
    else {
        // Stop the move sound when not moving
        moveSound.stop();

        // Reset the frame to the initial position if not moving
        XIndex = 0;
        sprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
    }

    // Zapisanie ostatniej poprawnej pozycji gracza
    lastValidPosition = position;
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(boundingRectangle);
}

bool Player::CheckCollision(const sf::RectangleShape& other) {
    return boundingRectangle.getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::RectangleShape& Player::GetBoundingRectangle() {
    return boundingRectangle;
}

sf::Sprite Player::getSprite() const {
    return sprite;
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::RevertMove() {
    sprite.setPosition(lastValidPosition);
    boundingRectangle.setPosition(lastValidPosition);
}

std::vector<std::string> Player::getInventory() const {
    return inventory;
}

void Player::useItem(const std::string& item) {
    if (item == "Potion") {
        health += 50;
        if (health > max_health) {
            health = max_health;
        }
        std::cout << "Used Potion. Health is now " << health << std::endl;
    }
    else if (item == "Elixir") {
        std::cout << "Used Elixir." << std::endl;
    }
    else if (item == "Revive") {
        std::cout << "Used Revive." << std::endl;
    }
    removeItem(item);
}

void Player::removeItem(const std::string& item) {
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

void Player::addItem(const std::string& item) {
    inventory.push_back(item); // Dodawanie przedmiotu do ekwipunku
}

void Player::basicAttack(Character& opponent) {
    opponent.health -= basicAttackDamage;
    std::cout << name << " used Player's Basic Attack on " << opponent.name << " for " << basicAttackDamage << " damage.\n";
}

void Player::specialAttack(Character& opponent) {
    opponent.health -= specialAttackDamage;
    std::cout << name << " used Player's Special Attack on " << opponent.name << " for " << specialAttackDamage << " damage.\n";
}
