#include "Clickable.h"

#include <iostream>
#include <sstream>

Clickable::Clickable(sf::Vector2f size, sf::Color color, sf::Color hoverColor, sf::Color clickColor) 
    : Rectangle(size, color), defaultColor(color), hoverColor(hoverColor), clickColor(clickColor) {
}

void Clickable::checkCursorOn(sf::RenderWindow & window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (shape.getGlobalBounds().contains(mousePosF)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            shape.setFillColor(clickColor); // Change color on click
            isClicked = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isClicked) {
            shape.setFillColor(defaultColor);
            isClicked = false;
            onClick(); // Call onClick when mouse button is released
        }
        else {
            shape.setFillColor(hoverColor); // Change color on hover
        }
    } else {
        shape.setFillColor(defaultColor); // Default color
    }
}

void Clickable::onClick() {
    std::cout << "Clickable was clicked!" << std::endl;
}

Clickable::~Clickable() = default;