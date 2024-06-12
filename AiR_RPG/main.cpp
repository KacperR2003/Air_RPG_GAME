﻿#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <sstream>
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

void saveGame(const Player& player, const Enemy& enemy, const std::vector<std::vector<int>>& mapState) {
    std::ofstream saveFile("savegame.txt");
    if (saveFile.is_open()) {
        // Zapisz stan gracza
        saveFile << "Player\n";
        saveFile << player.getName() << "\n";
        saveFile << player.getHealth() << "\n";
        saveFile << player.getPosition().x << " " << player.getPosition().y << "\n";

        // Zapisz stan wroga
        saveFile << "Enemy\n";
        saveFile << enemy.getName() << "\n";
        saveFile << enemy.getHealth() << "\n";
        saveFile << enemy.getPosition().x << " " << enemy.getPosition().y << "\n";

        // Zapisz stan mapy
        saveFile << "Map\n";
        for (const auto& row : mapState) {
            for (const auto& tile : row) {
                saveFile << tile << " ";
            }
            saveFile << "\n";
        }

        saveFile.close();
        std::cout << "Gra zapisana pomyślnie!" << std::endl;
    }
    else {
        std::cerr << "Błąd podczas zapisywania gry!" << std::endl;
    }
}
bool LoadGameState(const std::string& filename, Player& player, Enemy& enemies) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        iss >> word;

        if (word == "Player") {
            float x, y;
            std::getline(file, line);
            std::istringstream(line) >> word >> x;
            std::getline(file, line);
            std::istringstream(line) >> word >> y;
            player.getSprite().setPosition(x, y);

            std::getline(file, line);
            std::istringstream inventoryStream(line);
            inventoryStream >> word; // Pomiń ekwpipunek
            std::vector<std::string> inventory;
            while (inventoryStream >> word) {
                inventory.push_back(word);
            }
            for (const auto& item : inventory) {
                player.addItem(item);
            }
        }
        else if (word == "Enemy") {
            Enemy enemy("EnemyName", 100, 10, 20); // Zastąp odpowiednimi wartościami
            float x, y;
            std::getline(file, line);
            std::istringstream(line) >> word >> x;
            std::getline(file, line);
            std::istringstream(line) >> word >> y;
            enemy.getSprite().setPosition(x, y);

            std::getline(file, line);
            std::istringstream inventoryStream(line);
            inventoryStream >> word; // Pomiń ekwipunek
            std::vector<std::string> inventory;
            while (inventoryStream >> word) {
                inventory.push_back(word);
            }
            for (const auto& item : inventory) {
                enemy.addItem(item);
            }
        }
    }

    file.close();
    return true;
}
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
                            if (LoadGameState("savegame.txt", player, enemy)) {
                                std::cout << "Game loaded successfully!" << std::endl;
                                gameState = MapState; // Przełącz się na stan mapy po załadowaniu gry
                            }
                            else {
                                std::cout << "Failed to load the game!" << std::endl;
                            } // Zaladuj grę
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
                // Aktualizowanie pozycji na mapie
                player.Update(window);
                enemy.Update(window);

                // Sprawdzanie czy wystepuje kolizja
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
                            saveGame(player, enemy, grid);//Zapis gry
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
                //Scena walki
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
        //Obsługa scen
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