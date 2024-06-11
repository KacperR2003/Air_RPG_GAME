// Dialog.cpp

#include "Dialog.h"

Dialog::Dialog(const std::string& fontPath, const sf::Vector2f& pos, unsigned int charSize, sf::Color txtColor, float bgHeight, float bgWidth, sf::Color bgColor, float timeChar)
    : position(pos), characterSize(charSize), textColor(txtColor), backgroundHeight(bgHeight), backgroundWidth(bgWidth), backgroundColor(bgColor), timePerCharacter(timeChar), elapsedTime(0.f), currentCharIndex(0)
{
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font");
    }
    text.setFont(font);
    text.setPosition(position);
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);

    background.setSize(sf::Vector2f(backgroundWidth, backgroundHeight));
    background.setFillColor(backgroundColor);
    background.setPosition(0, pos.y);
}

void Dialog::addDialog(const std::string& dialog) {
    dialogs.push(dialog);
}

void Dialog::nextDialog() {
    if (!dialogs.empty()) {
        currentDialog = dialogs.front();
        dialogs.pop();
        currentCharIndex = 0;
        text.setString("");
        elapsedTime = 0.f;
    }
}

void Dialog::update(float deltaTime) {
    if (currentCharIndex < currentDialog.length()) {
        elapsedTime += deltaTime;
        if (elapsedTime >= timePerCharacter) {
            currentCharIndex++;
            text.setString(currentDialog.substr(0, currentCharIndex));
            elapsedTime = 0.f;
        }
    }
}

void Dialog::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(text);
}

bool Dialog::isComplete() const {
    return currentCharIndex >= currentDialog.length();
}

void Dialog::skipToEndOfCurrentDialog() {
    currentCharIndex = currentDialog.size(); // Display the entire dialog
    text.setString(currentDialog);
}

std::string Dialog::getCurrentDialog() const {
    return currentDialog;
}
