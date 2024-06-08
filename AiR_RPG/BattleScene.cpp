#include "BattleScene.h"
#include <iostream>

BattleScene::BattleScene(Player& player, Enemy& enemy)
    : player(player),
    enemy(enemy),
    playerTurn(true),
    running(true),
    selectedOption(0) {
    menuOptions = { "Attack", "Special Attack", "Items", "Run" };

    std::srand(static_cast<unsigned>(std::time(nullptr))); // Initialize random seed
}

void BattleScene::start() {
    running = true;
}

bool BattleScene::isRunning() const {
    return running;
}

void BattleScene::processEvents(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        handlePlayerInput(event.key.code, window);
    }
}

void BattleScene::update() {
    if (!playerTurn) {
        enemyTurn();  // Wywo³anie metody enemyTurn
        playerTurn = true;
    }
}

void BattleScene::render(sf::RenderWindow& window) {
    drawText(window, player.getName() + " HP: " + std::to_string(player.getHealth()), 50, 50);
    drawText(window, enemy.getName() + " HP: " + std::to_string(enemy.getHealth()), 1600, 50);
    // Renderowanie spritów gracza i przeciwnika
    sf::Sprite playerSprite = player.getSprite(); // Metoda do pobierania sprite'a
    sf::Sprite enemySprite = enemy.getSprite();   // Metoda do pobierania sprite'a

    // Ustawiamy pozycjê spritów pod nazwami
    playerSprite.setPosition(50, 100);
    enemySprite.setPosition(1600, 100);

    window.draw(playerSprite);
    window.draw(enemySprite);
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

void BattleScene::handlePlayerInput(sf::Keyboard::Key key, sf::RenderWindow& window) {
    if (key == sf::Keyboard::Up) {
        selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
    }
    else if (key == sf::Keyboard::Down) {
        selectedOption = (selectedOption + 1) % menuOptions.size();
    }
    else if (key == sf::Keyboard::Z) {
        executeAction(selectedOption, window);
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

void BattleScene::executeAction(int option, sf::RenderWindow& window) {
    switch (option) {
    case 0:
        player.basicAttack(enemy);
        break;
    case 1:
        player.specialAttack(enemy);
        break;
    case 2:
        openInventory(window);// Potrzebujemy obiektu window, przekazanego do openInventory
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

// Dodanie metody openInventory do obs³ugi ekwipunku
void BattleScene::openInventory(sf::RenderWindow& window) {
    std::vector<std::string> inventory = player.getInventory();
    bool inInventory = true;
    int selectedItemIndex = 0;

    while (inInventory) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                inInventory = false;
            }
            else if (event.type == sf::Event::KeyPressed) {
                handleInventoryInput(window, event.key.code, selectedItemIndex, inventory.size());
                if (event.key.code == sf::Keyboard::Escape) {
                    inInventory = false; // Wyjœcie z ekwipunku
                }
                else if (event.key.code == sf::Keyboard::Z) {
                    player.useItem(inventory[selectedItemIndex]);
                    inInventory = false; // Wyjœcie z ekwipunku po u¿yciu przedmiotu
                }
            }
        }

        window.clear();
        render(window); // Renderuj scenê walki w tle

        // Renderuj ekwipunek jako dwie kolumny
        for (size_t i = 0; i < inventory.size(); ++i) {
            int x = (i % 2) * 200 + 100;
            int y = (i / 2) * 30 + 200;
            if (i == selectedItemIndex) {
                drawText(window, "> " + inventory[i], x, y);
            }
            else {
                drawText(window, inventory[i], x, y);
            }
        }

        window.display();
    }
}

// Metoda do obs³ugi sterowania ekwipunkiem
void BattleScene::handleInventoryInput(sf::RenderWindow& window, sf::Keyboard::Key key, int& selectedItemIndex, int itemCount) {
    if (key == sf::Keyboard::Up) {
        selectedItemIndex = (selectedItemIndex - 2 + itemCount) % itemCount; // Przechodzenie w górê (co druga pozycja)
    }
    else if (key == sf::Keyboard::Down) {
        selectedItemIndex = (selectedItemIndex + 2) % itemCount; // Przechodzenie w dó³ (co druga pozycja)
    }
    else if (key == sf::Keyboard::Left) {
        selectedItemIndex = (selectedItemIndex - 1 + itemCount) % itemCount; // Przechodzenie w lewo (jedna pozycja w lewo)
    }
    else if (key == sf::Keyboard::Right) {
        selectedItemIndex = (selectedItemIndex + 1) % itemCount; // Przechodzenie w prawo (jedna pozycja w prawo)
    }
}
