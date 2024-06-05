#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Player.h"
#include "Enemy.h"

class BattleScene {
public:
    BattleScene(Player& player, Enemy& enemy);
    void start();
    bool isRunning() const;
    void processEvents(sf::Event event);
    void update();
    void render(sf::RenderWindow& window);

private:
    Player& player;
    Enemy& enemy;
    bool playerTurn;
    bool running;
    int selectedOption;
    std::vector<std::string> menuOptions;

    void handlePlayerInput(sf::Keyboard::Key key);
    void drawText(sf::RenderWindow& window, const std::string& text, int x, int y);
    void drawMenu(sf::RenderWindow& window);
    void executeAction(int option);
    void enemyTurn();
};