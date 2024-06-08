#pragma once

#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class BattleScene {
public:
    BattleScene(Player& player, Enemy& enemy);

    void start();
    bool isRunning() const;
    void processEvents(sf::Event event, sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);

private:
    Player& player;
    Enemy& enemy;
    bool playerTurn;
    bool running;
    int selectedOption;
    std::vector<std::string> menuOptions;

    void handlePlayerInput(sf::Keyboard::Key key, sf::RenderWindow& window);
    void drawText(sf::RenderWindow& window, const std::string& text, int x, int y);
    void drawMenu(sf::RenderWindow& window);
    void executeAction(int option, sf::RenderWindow& window);
    void enemyTurn();

    void openInventory(sf::RenderWindow& window);  // Dodajemy argument window
    void handleInventoryInput(sf::RenderWindow& window, sf::Keyboard::Key key, int& selectedItemIndex, int itemCount); // Dodajemy argument window
};
