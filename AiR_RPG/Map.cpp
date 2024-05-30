#include "Map.h"

Map::Map(int rows, int cols, const std::string& floorTexturePath, const std::string& wallTexturePath, const std::string& roadTexturePath)
    : rows(rows), cols(cols)
{
    grid.resize(rows, std::vector<int>(cols, 0));

    if (!floorTexture.loadFromFile(floorTexturePath)) {
        std::cerr << "Failed to load floor textures!" << std::endl;
    }
    if (!wallTexture.loadFromFile(wallTexturePath)) {
        std::cerr << "Failed to load wall textures!" << std::endl;
    }
    if (!roadTexture.loadFromFile(roadTexturePath)) {
        std::cerr << "Failed to load road textures!" << std::endl;
    }

    floorSprite.setTexture(floorTexture);
    wallSprite.setTexture(wallTexture);
    roadSprite.setTexture(roadTexture);
}

void Map::ustaw_stala_mape(const std::vector<std::vector<int>>& newGrid)
{
    if (newGrid.size() != rows || newGrid[0].size() != cols) {
        std::cerr << "Invalid grid dimensions!" << std::endl;
        return;
    }
    grid = newGrid;

    // Resetowanie wektora prostok¹tów kolizji
    wallColliders.clear();

    // Tworzenie prostok¹tów kolizji dla œcian
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) { // Jeœli kafelek jest œcian¹
                sf::RectangleShape wallCollider;
                wallCollider.setSize(sf::Vector2f(64, 64)); // Rozmiar kafelka
                wallCollider.setPosition(j * 64, i * 64); // Pozycja na mapie
                wallColliders.push_back(wallCollider);
            }
        }
    }
}

void Map::aktualizuj_mape(sf::RenderWindow& window)
{
    // Set the position of the sprites outside the loop
    floorSprite.setPosition(0, 0);
    wallSprite.setPosition(0, 0);
    roadSprite.setPosition(0, 0);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 0) {
                floorSprite.setPosition(j * 64, i * 64);
                window.draw(floorSprite);
            }
            else if (grid[i][j] == 1) {
                wallSprite.setPosition(j * 64, i * 64);
                window.draw(wallSprite);
            }
            else if (grid[i][j] == 2) {
                roadSprite.setPosition(j * 64, i * 64);
                window.draw(roadSprite);
            }
        }
    }

    // Rysowanie prostok¹tów kolizji dla œcian
    for (const auto& wallCollider : wallColliders) {
        window.draw(wallCollider);
    }
}

bool Map::kolizja(const sf::FloatRect& boundingBox)
{
    for (const auto& wallCollider : wallColliders) {
        if (boundingBox.intersects(wallCollider.getGlobalBounds())) {
            return true; // Kolizja z jedn¹ ze œcian
        }
    }
    return false; // Brak kolizji
}
