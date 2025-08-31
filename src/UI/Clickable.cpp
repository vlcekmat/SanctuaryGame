#include "Clickable.h"

void Clickable::checkCursorOn(sf::RenderWindow & window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (shape.getGlobalBounds().contains(mousePosF)) {
        shape.setFillColor(sf::Color::Red); // Change color on hover
    } else {
        shape.setFillColor(sf::Color::White); // Default color
    }
}

Clickable::~Clickable() = default;