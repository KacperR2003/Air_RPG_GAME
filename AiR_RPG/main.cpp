#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Map.h"
#include "Menu.h"
#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Options.h"
#include "MenuGame.h"
int max_health = 0;
enum GameState {
    MainMenu,
    MapState,
    OptionState,
    MapMenu,
    Battle,
    Exit
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1024), "Game");

    GameState gameState = MainMenu;

    Menu mainMenu(window.getSize().x, window.getSize().y);
    MenuGame mapMenu(window.getSize().x, window.getSize().y);
    std::vector<std::string> mapMenuOptions = { "Statystyki", "Zapisz", "Ekwipunek", "Wyjscie" };
    mapMenu.setOptions(mapMenuOptions);
    Options options(window.getSize().x, window.getSize().y);
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
            if (event.type == sf::Event::Closed)
                window.close();

            switch (gameState) {
            case MainMenu:
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        mainMenu.MoveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        mainMenu.MoveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Z) {
                        int selectedItem = mainMenu.GetPressedItem();
                        if (selectedItem == 0) {
                            gameState = MapState; // Nowa Gra
                        }
                        else if (selectedItem == 1) {
                            gameState = MapState; // Zaladuj grę
                        }
                        else if (selectedItem == 2) {
                            gameState = OptionState; // Opcje
                        }
                        else if (selectedItem == 3) {
                            window.close(); // Wyjście
                        }
                    }
                }
                break;

            case MapState:
                // Player and enemy input handling for map state
                player.Update(window);
                enemy.Update(window);

                // Checking for collision to initiate battle
                if (player.CheckCollision(enemy.getBoundingRectangle())) {
                    gameState = Battle;
                    battleScene.start();
                }

                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::M) {
                        gameState = MapMenu; // Przełączenie do menu mapy
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        gameState = MainMenu; // Powrót do głównego menu
                    }
                }
                break;

            case MapMenu:
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        mapMenu.MoveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        mapMenu.MoveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Z) {
                        int selectedItem = mapMenu.GetPressedItem();
                        if (selectedItem == 0) {
                            // Statystyki
                        }
                        else if (selectedItem == 1) {
                            // Zapisz grę
                        }
                        else if (selectedItem == 2) {
                            // Ekwipunek
                        }
                        else if (selectedItem == 3) {
                            gameState = MainMenu; // Wyjście do głównego menu
                        }
                    }
                    else if (event.key.code == sf::Keyboard::X) {
                        gameState = MapState; // Powrót do mapy
                    }
                }
                break;

            case Battle:
                if (battleScene.isRunning()) {
                    battleScene.processEvents(event, window);
                }
                else {
                    gameState = MapState;
                }
                break;

            case OptionState:
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::X) {
                        gameState = MainMenu; // Powrót do głównego menu
                    }
                }
                break;

            case Exit:
                window.close();
                break;
            }
        }

        window.clear();

        switch (gameState) {
        case MainMenu:
            mainMenu.draw(window);
            break;

        case MapState:
            map.aktualizuj_mape(window);
            player.Draw(window);
            enemy.Draw(window);
            break;

        case MapMenu:
            map.aktualizuj_mape(window);
            player.Draw(window);
            enemy.Draw(window);
            mapMenu.draw(window); // Rysowanie menu mapy
            break;

        case Battle:
            battleScene.update();
            battleScene.render(window);
            break;

        case OptionState:
            options.draw(window);
            break;

        case Exit:
            window.close();
            break;
        }

        window.display();
    }

    return 0;
}