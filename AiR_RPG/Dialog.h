#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <queue>

class Dialog {
private:
    sf::Font font;               // Font used for the dialog text
    sf::Text text;               // SFML Text object to render the dialog
    sf::RectangleShape background; // Background for the dialog box
    std::queue<std::string> dialogs; // Queue of dialog strings
    sf::Vector2f position;       // Position of the dialog box
    unsigned int characterSize;  // Size of the text
    sf::Color textColor;         // Color of the text
    float backgroundHeight;      // Height of the dialog background
    float backgroundWidth;       // Width of the dialog background
    sf::Color backgroundColor;   // Color of the background

    float timePerCharacter;      // Time interval between each character being displayed
    float elapsedTime;           // Time elapsed since the last character was added
    size_t currentCharIndex;     // Current index of the character to display
    std::string currentDialog;   // Current dialog string being displayed

public:
    Dialog(const std::string& fontPath, const sf::Vector2f& pos, unsigned int charSize, sf::Color txtColor, float bgHeight, float bgWidth, sf::Color bgColor, float timeChar);
    void addDialog(const std::string& dialog);
    void nextDialog();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isComplete() const;
    void skipToEndOfCurrentDialog();
    std::string getCurrentDialog() const;
};