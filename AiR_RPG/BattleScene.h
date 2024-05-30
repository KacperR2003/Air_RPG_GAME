#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class BattleScene {
public:
    BattleScene();
    void run();

private:
    sf::RenderWindow window;
    Player player;
    Enemy enemy;
    bool playerTurn;

    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void drawText(const std::string& text, int x, int y);
};

