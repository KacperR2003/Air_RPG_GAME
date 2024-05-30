#include "BattleScene.h"

BattleScene::BattleScene()
    : window(sf::VideoMode(800, 600), "Turn-Based Combat"),
    player("Player", 100, 10, 25),
    enemy("Enemy", 100, 10, 25),
    playerTurn(true) {}

void BattleScene::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void BattleScene::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
            handlePlayerInput(event.key.code, true);
    }
}

void BattleScene::update() {
    // Placeholder for any logic updates if needed
}

void BattleScene::render() {
    window.clear();

    drawText(player.name + " HP: " + std::to_string(player.health), 50, 50);
    drawText(enemy.name + " HP: " + std::to_string(enemy.health), 600, 50);

    if (player.health <= 0) {
        drawText("Enemy Wins!", 300, 300);
    }
    else if (enemy.health <= 0) {
        drawText("Player Wins!", 300, 300);
    }
    else {
        if (playerTurn) {
            drawText("Player's Turn", 300, 300);
        }
        else {
            drawText("Enemy's Turn", 300, 300);
        }
    }

    window.display();
}

void BattleScene::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (isPressed) {
        if (key == sf::Keyboard::A) {
            if (playerTurn) {
                player.basicAttack(enemy);
            }
            else {
                enemy.basicAttack(player);
            }
            playerTurn = !playerTurn;
            sf::sleep(sf::seconds(1));
        }

        if (key == sf::Keyboard::S) {
            if (playerTurn) {
                player.specialAttack(enemy);
            }
            else {
                enemy.specialAttack(player);
            }
            playerTurn = !playerTurn;
            sf::sleep(sf::seconds(1));
        }
    }
}

void BattleScene::drawText(const std::string& text, int x, int y) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(24);
    sfText.setFillColor(sf::Color::White);
    sfText.setPosition(x, y);

    window.draw(sfText);
}