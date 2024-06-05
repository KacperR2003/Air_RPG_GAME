#include "BattleScene.h"
#include <iostream>

BattleScene::BattleScene(Player& player, Enemy& enemy)
    : player(player),
    enemy(enemy),
    playerTurn(true),
    running(true),
    selectedOption(0) {
    menuOptions.push_back("Attack");
    menuOptions.push_back("Special Attack");
    menuOptions.push_back("Items");
    menuOptions.push_back("Run");

    std::srand(static_cast<unsigned>(std::time(nullptr))); // Initialize random seed
}
void BattleScene::start() {
    running = true;
}

bool BattleScene::isRunning() const {
    return running;
}

void BattleScene::processEvents(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        handlePlayerInput(event.key.code);
    }
}

void BattleScene::update() {
    if (!playerTurn) {
        enemyTurn();
        playerTurn = true;
    }
}

void BattleScene::render(sf::RenderWindow& window) {
    drawText(window, player.getName() + " HP: " + std::to_string(player.getHealth()), 50, 50);
    drawText(window, enemy.getName() + " HP: " + std::to_string(enemy.getHealth()), 1600, 50);

    if (player.getHealth() <= 0) {
        drawText(window, "Enemy Wins!", 960, 512);
    }
    else if (enemy.getHealth() <= 0) {
        drawText(window, "Player Wins!", 960, 512);
    }
    else {
        if (playerTurn) {
            drawText(window, "Player's Turn", 960, 512);
        }
        else {
            drawText(window, "Enemy's Turn", 960, 512);
        }
        drawMenu(window);
    }
}

void BattleScene::handlePlayerInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Up) {
        selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
    }
    else if (key == sf::Keyboard::Down) {
        selectedOption = (selectedOption + 1) % menuOptions.size();
    }
    else if (key == sf::Keyboard::Z) {
        executeAction(selectedOption);
        if (selectedOption != 3) {
            playerTurn = false;
        }
    }
}

void BattleScene::drawText(sf::RenderWindow& window, const std::string& text, int x, int y) {
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

void BattleScene::drawMenu(sf::RenderWindow& window) {
    for (size_t i = 0; i < menuOptions.size(); ++i) {
        if (i == selectedOption) {
            drawText(window, "> " + menuOptions[i], 50, 924 + i * 30);
        }
        else {
            drawText(window, menuOptions[i], 50, 924 + i * 30);
        }
    }
}

void BattleScene::executeAction(int option) {
    switch (option) {
    case 0:
        player.basicAttack(enemy);
        break;
    case 1:
        player.specialAttack(enemy);
        break;
    case 2:
        std::cout << "Items selected (no implementation)\n";
        break;
    case 3:
        std::cout << "Run selected\n";
        running = false;
        break;
    default:
        break;
    }
    sf::sleep(sf::seconds(1));
}

void BattleScene::enemyTurn() {
    enemy.performRandomAttack(player);
    sf::sleep(sf::seconds(1));
}
