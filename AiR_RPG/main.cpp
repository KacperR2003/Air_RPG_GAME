#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Map.h"

//Pisanie Textu
void drawText(sf::RenderWindow& window, const std::string& text, int x, int y) {
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

int main()
{
	//-------------------------------- INITIALIZE --------------------------------

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1920, 1024), "Air RPG", sf::Style::Default, settings);

	Player player("Player", 100, 10, 25);
	player.Initialize();
	Enemy enemy("Enemy", 100, 10, 25);
	enemy.Initialize();
	//-------------------------------- INITIALIZE --------------------------------
	//-------------------------------- LOAD --------------------------------
	player.Load();
	enemy.Load();

	Map map(16, 30, "Assets/Map/Textures/floor.png", "Assets/Map/Textures/wall.png", "Assets/Map/Textures/road.png");


	std::vector<std::vector<int>> staticGrid = {
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
	};

	map.ustaw_stala_mape(staticGrid);

	//-------------------------------- LOAD --------------------------------

	//main game loop
	while (window.isOpen())
	{
		//-------------------------------- UPDATE --------------------------------
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		player.Update(window);
		enemy.Update(window);



		//-------------------------------- UPDATE --------------------------------

		//-------------------------------- DRAW --------------------------------
		if (player.CheckCollision(enemy.getBoundingRectangle()))
		{
			bool playerTurn = true;

			while (window.isOpen()) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed)
						window.close();
				}

				window.clear();

				drawText(window, player.name + " HP: " + std::to_string(player.health), 50, 50);
				drawText(window, enemy.name + " HP: " + std::to_string(enemy.health), 600, 50);

				if (player.health <= 0) {
					drawText(window, "Enemy Wins!", 300, 300);
				}
				else if (enemy.health <= 0) {
					drawText(window, "Player Wins!", 300, 300);
				}
				else {
					if (playerTurn) {
						drawText(window, "Player's Turn", 300, 300);
					}
					else {
						drawText(window, "Enemy's Turn", 300, 300);
					}
				}

				window.display();

				if (player.health > 0 && enemy.health > 0) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
						if (playerTurn) {
							player.basicAttack(enemy);
						}
						else {
							enemy.basicAttack(player);
						}
						playerTurn = !playerTurn;
						sf::sleep(sf::seconds(1));
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
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
		}
		else
		{
			map.aktualizuj_mape(window);
		}
		player.Update(window); // Aktualizuj pozycjê gracza na podstawie klawiszy klawiatury

		
		map.aktualizuj_mape(window);
		player.Draw(window);
		enemy.Draw(window);

		window.display();
		//-------------------------------- DRAW --------------------------------
	}

	return 0;
}