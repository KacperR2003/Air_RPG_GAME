#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Map.h"
#include "Menu.h"
#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
int max_health = 0;
enum GameState {
    MainMenu,
    MapState,
    Battle,
    Exit
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1024), "Game");

    GameState gameState = MainMenu;

    Menu menu(window.getSize().x, window.getSize().y);
    Player player("Player", 100, 10, 20);
    Enemy enemy("Enemy", 50, 5, 15);
    BattleScene battleScene(player, enemy);

    player.Initialize();
    player.Load();
    enemy.Initialize();
    enemy.Load();

    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    Map map(grid.size(), grid[0].size(), "Assets/Map/Textures/floor.png", "Assets/Map/Textures/wall.png", "Assets/Map/Textures/road.png");
    map.ustaw_stala_mape(grid);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (gameState == MainMenu) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.MoveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        menu.MoveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Return) {
                        int selectedItem = menu.GetPressedItem();
                        if (selectedItem == 0) {
                            gameState = MapState;
                        }
                        else if (selectedItem == 3) {
                            window.close();
                        }
                    }
                }
                else if (gameState == MapState) {
                    // Player input handling for map state
                    player.Update(window);
                    // Enemy input handling for map state
                    enemy.Update(window);

                    if (player.CheckCollision(enemy.getBoundingRectangle())) {
                        gameState = Battle;
                        battleScene.start();
                    }
                }
                else if (gameState == Battle) {
                    if (battleScene.isRunning()) {
                        battleScene.processEvents(event, window);
                    }
                    else {
                        gameState = MapState;
                    }
                }
                break;
            default:
                break;
            }
        }
        player.Update(window);
        enemy.Update(window);

        window.clear();

        if (gameState == MainMenu) {
            menu.draw(window);
        }
        else if (gameState == MapState) {
            map.aktualizuj_mape(window);
            player.Draw(window);
            enemy.Draw(window);
        }
        else if (gameState == Battle) {
            battleScene.update();
            battleScene.render(window);
        }

        window.display();
    }

    return 0;
}